#include <iostream>
#include <sgg/graphics.h>
#include <ImGui/imgui.h>

#define SETCOLOR(c, r, g, b) {c[0]=r; c[1]=g; c[2]=b;}

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
	ShowMenuDemoWindow();
}

struct GameState
{
	std::string m_asset_path = "assets\\";

	int m_window_width = 800;
	int m_window_height = 800;
	std::string m_window_title = "Project Cpp";

	float m_canvas_width = 10.0f;
	float m_canvas_height = 10.0f;

	std::string m_player_texture_path = m_asset_path + "boy2.png";
	int m_player_texture_size_width = 512.0f;
	int m_player_texture_size_height = 512.0f;
	float m_player_scale_x = 0.25f;
	float m_player_scale_y = 0.25f;

	// Offset from starting position in Canvas Units

	// Translation is defined from upper left corner of window
	// which means positive x : right
	//			   negative x : left
	//			   positive y : down
	//			   negative y : up

	float m_player_translation_x = 0.0f;
	float m_player_translation_y = 0.0f;

	// Rotation could also be specified here

	float m_player_pos_x = m_canvas_width / 2.0f + m_player_translation_x;
	float m_player_pos_y = m_canvas_height / 2.0f + m_player_translation_y;

	float m_player_size_width = (float)m_player_texture_size_width / m_window_width *
		m_canvas_width * m_player_scale_x;
	float m_player_size_height = (float)m_player_texture_size_height / m_window_height *
		m_canvas_height * m_player_scale_y;

	float m_player_velocity = 0.001f;

	// Acceleration could be specified here

	graphics::Brush m_player_brush;
	
	std::string m_platform_texture_path = m_asset_path + "iron.png";
	int m_platform_texture_size_width = 256.0f;
	int m_platform_texture_size_height = 64.0f;
	float m_platform_scale_x = 1.0f;
	float m_platform_scale_y = 1.0f;

	// Offset from starting position in Canvas Units

	float m_platform_translation_x = 0.0f;
	float m_platform_translation_y = 1.3f; // So that platform appears bellow player

	// Rotation could also be specified here

	float m_platform_pos_x = m_canvas_width / 2.0f + m_platform_translation_x;
	float m_platform_pos_y = m_canvas_height / 2.0f + m_platform_translation_y;

	float m_platform_size_width = (float)m_platform_texture_size_width / m_window_width *
		m_canvas_width * m_platform_scale_x;
	float m_platform_size_height = (float)m_platform_texture_size_height / m_window_height *
		m_canvas_height * m_platform_scale_y;

	float m_platform_velocity = 0.0f;

	// Acceleration could also be specified here

	graphics::Brush m_platform_brush;

};

GameState state;

void init()
{
	SETCOLOR(state.m_player_brush.fill_color, 1.0f, 1.0f, 1.0f);
	state.m_player_brush.fill_opacity = 1.0f;
	state.m_player_brush.outline_opacity = 0.0f;
	state.m_player_brush.texture = state.m_player_texture_path;

	SETCOLOR(state.m_platform_brush.fill_color, 1.0f, 1.0f, 1.0f);
	state.m_platform_brush.fill_opacity = 1.0f;
	state.m_platform_brush.outline_opacity = 0.0f;
	state.m_platform_brush.texture = state.m_platform_texture_path;
}

void draw()
{
	graphics::drawRect(state.m_platform_pos_x, state.m_platform_pos_y,
		state.m_platform_size_width, state.m_platform_size_height,
		state.m_platform_brush);

	graphics::drawRect(state.m_player_pos_x, state.m_player_pos_y,
		state.m_player_size_width, state.m_player_size_height,
		state.m_player_brush);
}

// dt is in milliseconds so / 1000.0f will make it in seconds

void update(float dt)
{
	// Delta time is in seconds
	float deltaTime = dt / 1000.0f;

	// Left movement of player
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		state.m_player_translation_x = -state.m_player_velocity * dt;
		state.m_player_pos_x += state.m_player_translation_x;
	}

	// Right movement of player
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		state.m_player_translation_x = state.m_player_velocity * dt;
		state.m_player_pos_x += state.m_player_translation_x;
	}

	// Up movement of player
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		state.m_player_translation_y = -state.m_player_velocity * dt;
		state.m_player_pos_y += state.m_player_translation_y;
	}

	// Down movement of player
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		state.m_player_translation_y = state.m_player_velocity * dt;
		state.m_player_pos_y += state.m_player_translation_y;
	}

}

int main()
{
	graphics::createWindow(state.m_window_width, state.m_window_height, state.m_window_title);
	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	graphics::setMenuFunction(menu);

	graphics::setCanvasSize(state.m_canvas_width, state.m_canvas_height);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();

	return 0;
}