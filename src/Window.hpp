#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>
#include <implot.h>

class Window
{
public:
	Window();
	~Window();


	void start();
	void stop();
private:
	void mainLoop();
	void renderGUI();
	static void PushStyleCompact()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));
	}
	static const char* uTC(const char8_t* str)
	{
		return reinterpret_cast<const char*> (str);
	}
	static void PopStyleCompact()
	{
		ImGui::PopStyleVar(2);
	}
	sf::RenderWindow window;
	bool isStarted = false;
	bool isTheResultReady = false;
	graphic lg, pw, gr;
};
Window::Window() :
	window(sf::VideoMode(1024, 728), L"LAB 4")
{}

Window::~Window()
{
}

void Window::start()
{
	if (isStarted)
	{
		return;
	}
	else
	{
		isStarted = true;
		mainLoop();
	}


}

void Window::stop()
{
	if (isStarted)
	{
		isStarted = false;
	}
}

void Window::mainLoop()
{
	if (!ImGui::SFML::Init(window)) return;
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF("Fonts/arial.ttf", 16.f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	ImGui::SFML::UpdateFontTexture();

	ImGui::StyleColorsLight();
	//ImGui::GetIO().FontGlobalScale = 1.5f;
	io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
	ImPlot::CreateContext();

	sf::Clock deltaClock;
	while (window.isOpen() && isStarted)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		renderGUI();
		window.clear();

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	ImPlot::DestroyContext();
}

void Window::renderGUI()
{
    static int n = 3;
	static int precision = 10;
	static bool limExWin = false;
	static std::string funk = "x - sqrt(x - 1)";
	static std::string lim1 = "2", lim2 = "10";
	static double dLim1 = 2, dLim2 = 10;
	

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("Main Window", nullptr,
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::LabelText("##label", uTC(u8"������������: "));

	ImGui::BeginGroup();
	ImGui::LabelText("##label", uTC(u8"������� ������� f(x):"));
	ImGui::InputText("##TBf", &funk);
	ImGui::EndGroup();

	ImGui::SameLine();
	ImGui::BeginGroup();
	ImGui::LabelText("##label", uTC(u8"������� �������:"));
	ImGui::InputText("##TBl1", &lim1);

	ImGui::InputText("##TBl2", &lim2);
	ImGui::EndGroup();
	float windowWidth = ImGui::GetContentRegionAvail().x;


	float sliderWidth = windowWidth / 3.0f;


	ImGui::PushItemWidth(sliderWidth);
	ImGui::SliderInt(uTC(u8"��������"), &precision, 0, 300);

	ImGui::SameLine();

	ImGui::PushItemWidth(sliderWidth);
	ImGui::SliderInt(uTC(u8"����"), &n, 1, 100);

	static bool lagrangeFlag = true;
	static bool picewiseFlag = true;

	ImGui::Checkbox(uTC(u8"����� ��������"), &lagrangeFlag );
	ImGui::SameLine();
	ImGui::Checkbox(uTC(u8"����� �������-�������� �������"), &picewiseFlag);

	ImGui::PopItemWidth();
	if (ImGui::Button(uTC(u8"����������")))
	{
		mu::Parser parser;

		try
		{
			parser.SetExpr(lim1);
			dLim1 = parser.Eval();
			parser.SetExpr(lim2);
			dLim2 = parser.Eval();

			if (lagrangeFlag) {
				lg = calcLagGraphic(dLim1, dLim2, n, funk, precision);
			}
			if (picewiseFlag) {
				pw = calcPieceGraphic(dLim1, dLim2, n, funk, precision);
			}
			gr = getGraph(dLim1, dLim2, n, funk, precision);

			/*for (int i = 0; i < pw.x.size(); i++) {
				cout << pw.x[i] << " " << pw.y[i] << endl;
			}*/
		}
		catch (mu::Parser::exception_type& e)
		{
			std::cerr << e.GetMsg() << std::endl;
			limExWin = true;
			isTheResultReady = false;
			goto exEnd;
		}
		isTheResultReady = true;

	}
	if (isTheResultReady)
	{
		ImGui::BeginChild("result", ImVec2(0, 1280), true);
		{
			ImGui::LabelText("##label", uTC(u8"������:"));

			if (ImPlot::BeginPlot("##plot")) {
				ImPlot::SetupAxes(uTC(u8"X"), uTC(u8"Y"));
				if (lagrangeFlag) {
					ImPlot::SetNextLineStyle(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
					ImPlot::PlotLine("##plot", lg.x.data(), lg.y.data(), lg.y.size());
				}
				if (picewiseFlag) {
					ImPlot::SetNextLineStyle(ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
					ImPlot::PlotLine("##plot", pw.x.data(), pw.y.data(), pw.y.size());
				}
				ImPlot::SetNextLineStyle(ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
				ImPlot::PlotLine("##plot", gr.x.data(), gr.y.data(), gr.y.size());
				ImPlot::EndPlot();
			}
			


		}
		ImGui::EndChild();
	}

exEnd:
	if (limExWin)
	{
		ImGui::Begin(uTC(u8"������!"), &limExWin, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text(uTC(u8"������� ������� ������� ��� �������"));
		if (ImGui::Button(uTC(u8"�������")))
			limExWin = false;
		ImGui::End();
	}

	ImGui::End();
}

