#include <iostream>
#include <sgg/graphics.h>
#include <ImGui/imgui.h>
#include "GameState.h"

/*
* 
*/
bool BeginWindow(std::string name = "")
{
	return ImGui::Begin(name.c_str());
}
/*
* 
*/
void EndWindow()
{
	ImGui::End();
}

/*
* 
*/
void IntSlider(unsigned int numInts, int* ints, int min, int max, std::string name = "", float sliderSpeed = 1.0f)
{
	if (numInts == 1)
	{
		ImGui::DragInt(name.c_str(), & (ints[0]), sliderSpeed, min, max);
	}
	else if (numInts == 2)
	{
		ImGui::DragInt2(name.c_str(), &(ints[0]), sliderSpeed, min, max);
	}
	else if (numInts == 3)
	{
		ImGui::DragInt3(name.c_str(), &(ints[0]), sliderSpeed, min, max);
	}
	else if (numInts == 4)
	{
		ImGui::DragInt4(name.c_str(), &(ints[0]), sliderSpeed, min, max);
	}
	else
	{
		std::cout << "Wrong number of ints: " << numInts << " given to IntSlider!" << std::endl;
	}
}

/*
* 
*/
void FloatSlider(unsigned int numFloats, float* floats, float min, float max, std::string name = "", unsigned int numDecimals = 2, float sliderSpeed = 1.0f)
{
	std::string format = ("%." + std::to_string(numDecimals) + "f");
	
	if (numFloats == 1)
	{
		ImGui::DragFloat(name.c_str(), &(floats[0]), sliderSpeed, min, max, format.c_str());
	}
	else if (numFloats == 2)
	{
		ImGui::DragFloat2(name.c_str(), &(floats[0]), sliderSpeed, min, max, format.c_str());
	}
	else if (numFloats == 3)
	{
		ImGui::DragFloat3(name.c_str(), &(floats[0]), sliderSpeed, min, max, format.c_str());
	}
	else if (numFloats == 4)
	{
		ImGui::DragFloat4(name.c_str(), &(floats[0]), sliderSpeed, min, max, format.c_str());
	}
	else
	{
		std::cout << "Wrong number of floats: " << numFloats << " given to FloatSlider!" << std::endl;
	}
}

/*
* 
*/
void Button(bool& isPressed, std::string name = "", float width = 0.0f, float height = 0.0f)
{
	isPressed = ImGui::Button(name.c_str(), {width, height});
}

/*
* 
*/
void Radio(int & choice, int countChoices, std::string * names)
{
	for (int i = 0; i < countChoices - 1; i++)
	{
		ImGui::RadioButton(names[i].c_str(), &choice, i); ImGui::SameLine();
	}

	ImGui::RadioButton(names[countChoices - 1].c_str(), &choice, countChoices - 1);
}

/*
* 
*/
void Checkbox(bool& isChecked, std::string name = "")
{
	ImGui::Checkbox(name.c_str(), &isChecked);
}

/*
* 
*/
void ColorPicker(int numChannels, float* colorChannels, std::string name = "", bool normalized = true)
{
	ImGuiColorEditFlags flags = 0;

	if (normalized)
	{
		flags |= ImGuiColorEditFlags_Float;
	}

	if (numChannels == 3)
	{
		ImGui::ColorEdit3(name.c_str(), &(colorChannels[0]), flags);
	}
	else if (numChannels == 4)
	{
		ImGui::ColorEdit4(name.c_str(), &(colorChannels[0]), flags);
	}
	else
	{
		std::cout << "Wrong number of channels passed : " << numChannels << " Can be only 3 or 4!" << std::endl;
	}
}

/*
* 
*/
void ShowMenuDemoWindow()
{
	ImGui::ShowDemoWindow();
}

/*
* 
*/
void SameLine()
{
	ImGui::SameLine();
}

void menu()
{
	//ShowMenuDemoWindow();
}

void init()
{
	GameState::inst()->init();
}

void update(float dt)
{
	GameState::inst()->update(dt);
}

void draw()
{
	GameState::inst()->draw();
}

int main()
{
	init();
	
	graphics::createWindow(GameState::inst()->getWindowWidth(), GameState::inst()->getWindowHeight(), GameState::inst()->getWindowTitle());

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	//graphics::setMenuFunction(menu);

	graphics::setCanvasSize(GameState::inst()->getCanvasWidth(), GameState::inst()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();
	return 0;
}