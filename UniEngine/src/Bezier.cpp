#include "pch.h"
#include "Bezier.h"

#include <ctime>

UniEngine::BezierCubic2D::BezierCubic2D()
{
    m_controlPoints[0] = glm::vec2(0);
    m_controlPoints[1] = glm::vec2(0.5f, 0.0f);
    m_controlPoints[2] = glm::vec2(0.5f, 1.0f);
    m_controlPoints[3] = glm::vec2(1, 1);
}
glm::vec2 UniEngine::BezierCubic2D::GetPoint(const float& t) const
{
    float t1 = 1.0f - t;
	
    return t1 * t1 * t1 * m_controlPoints[0] + 3.0f * t1 * t1 * t * m_controlPoints[1] + 3.0f * t1 * t * t * m_controlPoints[2] + t * t * t * m_controlPoints[3];
}
bool UniEngine::BezierCubic2D::Graph(const std::string& label)
{
    
    // visuals
    enum { SMOOTHNESS = 64 }; // curve smoothness: the higher number of segments, the smoother curve
    enum { CURVE_WIDTH = 4 }; // main curved line width
    enum { LINE_WIDTH = 1 }; // handlers: small lines width
    enum { GRAB_RADIUS = 8 }; // handlers: circle radius
    enum { GRAB_BORDER = 2 }; // handlers: circle border width
    enum { AREA_CONSTRAINED = true }; // should grabbers be constrained to grid area?
    enum { AREA_WIDTH = 0 }; // area width in pixels. 0 for adaptive size (will use max avail width)

    const ImGuiStyle& Style = ImGui::GetStyle();
    const ImGuiIO& IO = ImGui::GetIO();
    ImDrawList* DrawList = ImGui::GetWindowDrawList();
    ImGuiWindow* Window = ImGui::GetCurrentWindow();
    if (Window->SkipItems)
        return false;
    bool changed = false;
    // header and spacing
    if (ImGui::TreeNode(label.c_str())) {
        if(!m_fixed && ImGui::SliderFloat2("P0", &m_controlPoints[0].x, 0, 1, "%.3f", 1.0f)) changed = true;
		if(ImGui::SliderFloat2("P1", &m_controlPoints[1].x, 0, 1, "%.3f", 1.0f)) changed = true;
        if (ImGui::SliderFloat2("P2", &m_controlPoints[2].x, 0, 1, "%.3f", 1.0f))changed = true;
        if(!m_fixed && ImGui::SliderFloat2("P3", &m_controlPoints[3].x, 0, 1, "%.3f", 1.0f)) changed = true;
        int hovered = ImGui::IsItemActive() || ImGui::IsItemHovered(); // IsItemDragged() ?
        ImGui::Dummy(ImVec2(0, 3));

        // prepare canvas
        const float avail = ImGui::GetContentRegionAvailWidth();
        const float dim = AREA_WIDTH > 0 ? AREA_WIDTH : avail;
        ImVec2 Canvas(dim, dim);

        ImRect bb(Window->DC.CursorPos, Window->DC.CursorPos + Canvas);
        ImGui::ItemSize(bb);
        if (!ImGui::ItemAdd(bb, NULL))
            return changed;

        const ImGuiID id = Window->GetID(label.c_str());
        hovered |= 0 != ImGui::ItemHoverable(ImRect(bb.Min, bb.Min + ImVec2(avail, dim)), id);

        ImGui::RenderFrame(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg, 1), true, Style.FrameRounding);

        // background grid
        for (int i = 0; i <= Canvas.x; i += (Canvas.x / 4)) {
            DrawList->AddLine(
                ImVec2(bb.Min.x + i, bb.Min.y),
                ImVec2(bb.Min.x + i, bb.Max.y),
                ImGui::GetColorU32(ImGuiCol_TextDisabled));
        }
        for (int i = 0; i <= Canvas.y; i += (Canvas.y / 4)) {
            DrawList->AddLine(
                ImVec2(bb.Min.x, bb.Min.y + i),
                ImVec2(bb.Max.x, bb.Min.y + i),
                ImGui::GetColorU32(ImGuiCol_TextDisabled));
        }

        // eval curve
        ImVec2 Q[4] = { { m_controlPoints[0].x, m_controlPoints[0].y }, { m_controlPoints[1].x, m_controlPoints[1].y }, { m_controlPoints[2].x, m_controlPoints[2].y }, { m_controlPoints[3].x, m_controlPoints[3].y } };


        // control points: 2 lines and 2 circles
        {
            // handle grabbers
            ImVec2 mouse = ImGui::GetIO().MousePos, pos[2];
            float distance[2];

            for (int i = 1; i < 3; ++i) {
                pos[i - 1] = ImVec2(m_controlPoints[i].x, 1 - m_controlPoints[i].y) * (bb.Max - bb.Min) + bb.Min;
                distance[i - 1] = (pos[i - 1].x - mouse.x) * (pos[i - 1].x - mouse.x) + (pos[i - 1].y - mouse.y) * (pos[i - 1].y - mouse.y);
            }

            int selected = distance[0] < distance[1] ? 1 : 2;
            if (distance[selected - 1] < (4 * GRAB_RADIUS * 4 * GRAB_RADIUS))
            {
                ImGui::SetTooltip("(%4.3f, %4.3f)", m_controlPoints[selected].x, m_controlPoints[selected].y);

                if (ImGui::IsMouseClicked(0) || ImGui::IsMouseDragging(0)) {
                    float& px = m_controlPoints[selected].x += ImGui::GetIO().MouseDelta.x / Canvas.x;
                    float& py = m_controlPoints[selected].y -= ImGui::GetIO().MouseDelta.y / Canvas.y;
                    if (AREA_CONSTRAINED) {
                        px = (px < 0 ? 0 : (px > 1 ? 1 : px));
                        py = (py < 0 ? 0 : (py > 1 ? 1 : py));
                    }

                    changed = true;
                }
            }
        }

        // if (hovered || changed) DrawList->PushClipRectFullScreen();
        std::vector<glm::vec2> results;
        results.resize(SMOOTHNESS + 1);
        for (int i = 0; i < SMOOTHNESS + 1; i++)
        {
            results[i] = GetPoint(static_cast<float>(i) / SMOOTHNESS);
        }
        // draw curve
        {
            ImColor color(ImGui::GetStyle().Colors[ImGuiCol_PlotLines]);
            for (int i = 0; i < SMOOTHNESS; ++i) {
                ImVec2 p = { results[i + 0].x, 1 - results[i + 0].y };
                ImVec2 q = { results[i + 1].x, 1 - results[i + 1].y };
                ImVec2 r(p.x * (bb.Max.x - bb.Min.x) + bb.Min.x, p.y * (bb.Max.y - bb.Min.y) + bb.Min.y);
                ImVec2 s(q.x * (bb.Max.x - bb.Min.x) + bb.Min.x, q.y * (bb.Max.y - bb.Min.y) + bb.Min.y);
                DrawList->AddLine(r, s, color, CURVE_WIDTH);
            }
        }

        // draw preview (cycles every 1s)
        static clock_t epoch = clock();
        ImVec4 white(ImGui::GetStyle().Colors[ImGuiCol_Text]);
        for (int i = 0; i < 3; ++i) {
            double now = ((clock() - epoch) / (double)CLOCKS_PER_SEC);
            float delta = ((int)(now * 1000) % 1000) / 1000.f; delta += i / 3.f; if (delta > 1) delta -= 1;
            int idx = (int)(delta * SMOOTHNESS);
            float evalx = results[idx].x; //
            float evaly = results[idx].y; // ImGui::BezierValue( delta, P );
            ImVec2 p0 = ImVec2(evalx, 1 - 0) * (bb.Max - bb.Min) + bb.Min;
            ImVec2 p1 = ImVec2(0, 1 - evaly) * (bb.Max - bb.Min) + bb.Min;
            ImVec2 p2 = ImVec2(evalx, 1 - evaly) * (bb.Max - bb.Min) + bb.Min;
            DrawList->AddCircleFilled(p0, GRAB_RADIUS / 2, ImColor(white));
            DrawList->AddCircleFilled(p1, GRAB_RADIUS / 2, ImColor(white));
            DrawList->AddCircleFilled(p2, GRAB_RADIUS / 2, ImColor(white));
        }

        // draw lines and grabbers
        float luma = ImGui::IsItemActive() || ImGui::IsItemHovered() ? 0.5f : 1.0f;
        ImVec4 pink(1.00f, 0.00f, 0.75f, luma), cyan(0.00f, 0.75f, 1.00f, luma);
        ImVec2 p0 = ImVec2(m_controlPoints[0].x, 1 - m_controlPoints[0].y) * (bb.Max - bb.Min) + bb.Min;
        ImVec2 p1 = ImVec2(m_controlPoints[1].x, 1 - m_controlPoints[1].y) * (bb.Max - bb.Min) + bb.Min;
        ImVec2 p2 = ImVec2(m_controlPoints[2].x, 1 - m_controlPoints[2].y) * (bb.Max - bb.Min) + bb.Min;
        ImVec2 p3 = ImVec2(m_controlPoints[3].x, 1 - m_controlPoints[3].y) * (bb.Max - bb.Min) + bb.Min;
        DrawList->AddLine(p0, p1, ImColor(white), LINE_WIDTH);
        DrawList->AddLine(p3, p2, ImColor(white), LINE_WIDTH);
        DrawList->AddCircleFilled(p1, GRAB_RADIUS, ImColor(white));
        DrawList->AddCircleFilled(p1, GRAB_RADIUS - GRAB_BORDER, ImColor(pink));
        DrawList->AddCircleFilled(p2, GRAB_RADIUS, ImColor(white));
        DrawList->AddCircleFilled(p2, GRAB_RADIUS - GRAB_BORDER, ImColor(cyan));

        // if (hovered || changed) DrawList->PopClipRect();
        ImGui::TreePop();
    }
    return changed;
}
