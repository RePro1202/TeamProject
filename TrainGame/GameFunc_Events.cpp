#include "GameFunc_Events.h"
#include <cstdlib>

Events::Events()
{
	SDL_Surface* event_surface = IMG_Load("../../Resources/Event.png");
	SDL_SetColorKey(event_surface, SDL_TRUE, SDL_MapRGB(event_surface->format, 112, 146, 190));
	events_texture_ = SDL_CreateTextureFromSurface(g_renderer, event_surface);
	SDL_FreeSurface(event_surface);

	SDL_Surface* command_surface = IMG_Load("../../Resources/wasd.png");
	command_texture_ = SDL_CreateTextureFromSurface(g_renderer, command_surface);
	command_texture_green_ = SDL_CreateTextureFromSurface(g_renderer, command_surface);	// �ùٸ� Ŀ�ǵ� �Է�(�ʷ�)
	SDL_SetTextureColorMod(command_texture_green_, 0, 255, 0);
	SDL_FreeSurface(command_surface);

	// ���� ���� �޼��� ��Ʈ
	output_font_ = TTF_OpenFont("../../Resources/ALBAS___.ttf", 80);
	black_ = { 0,0,0,0 };

	SDL_Surface* tmp_surface = TTF_RenderText_Blended(output_font_, "Success!", black_);
	output_texture_[0] = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_Surface* tmp_surface2 = TTF_RenderText_Blended(output_font_, "Fail", black_);
	output_texture_[1] = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);

	output_rect_ = { 0, 0, tmp_surface->w, tmp_surface->h };
	SDL_FreeSurface(tmp_surface);
	SDL_FreeSurface(tmp_surface2);
	TTF_CloseFont(output_font_);

	// �̺�Ʈ �̹��� src_rec
	events_source_rect_[EVENT_NONE] = { 800, 397 , 250 , 219 };		// Event Box
	events_source_rect_[EVENT_HEAT] = { 27, 8 ,247 , 300 };			// ����
	events_source_rect_[EVENT_COLD] = { 290, 10 , 255 , 300 };		// ����
	events_source_rect_[EVENT_MERCHANT] = { 608, 30 , 186 , 285 };	// �����
	events_source_rect_[EVENT_PSEUDO] = { 850, 51 , 138 , 229 };	// ���̺�
	events_source_rect_[EVENT_EMERGENCY] = { 76, 435 , 148 , 146 };	// �������
	events_source_rect_[EVENT_WILD] = { 286, 437 , 180 , 153 };		// �߻�����
	events_source_rect_[EVENT_DRUNK] = { 505, 422 , 215 , 196 };	// �밴

	// �̺�Ʈ �̹��� des_rec
	events_destination_rect_[EVENT_NONE] = { 210, 310 , 230 , 220 };
	for (int i = 1; i < 8; i++) {
		events_destination_rect_[i] = { 220, 320, 200, 180 };
	}

	// Ŀ�ǵ� �ҽ�
	command_source_rect_[0] = { 15, 15, 170 - 10 , 145 };
	command_source_rect_[1] = { 200, 15, 300 - 200, 145 };
	command_source_rect_[2] = { 340, 15, 440 - 340 , 145 };
	command_source_rect_[3] = { 470, 15, 590 - 470, 145 };
	
	// Ŀ�ǵ� ��ġ
	int x = 600;
	for (int i = 0; i < 5; i++) {
		command_destination_rect_[i] = { x, 300, 100, 80 };
		x += 100;
	}
	
	distance_ = 0;	// Runnig���� ������ distance�� ����
	eventState_ = false;	// �̺�Ʈ �߻������� �ƴ���
	random_ = rand() % 7 + 1;	// �̺�Ʈ ���� ������
	commandState_ = COMMAND_NONE;	// Ŀ�ǵ� ��������
	commandCount_ = 0;	// Ŀ�ǵ� ī��Ʈ
	passCount_ = 0;	// Ŀ�ǵ� ���� Ƚ��( Ŀ�ǵ带 ���� ��Ʈ �����ؾ� ��� ��� ���ؼ�)
	
	for (int i = 0; i < 5; i++) {
		command_[i] = 0;
		trueCommand_[i] = rand() % 4;	// ���� Ŀ�ǵ� ���� ����
	}
}

Events::~Events()
{
	SDL_DestroyTexture(events_texture_);
	SDL_DestroyTexture(command_texture_);
	SDL_DestroyTexture(command_texture_green_);
	SDL_DestroyTexture(output_texture_[0]);
	SDL_DestroyTexture(output_texture_[1]);
}

void Events::runEvent(int dis) {
	distance_ = dis;

	if (distance_ >= 2 && distance_ < 5) {
		eventSet();
		if (distance_ >= 4) {
			commandState_ = COMMAND_FAIL;
		}
	}
	else {
		commandState_ = COMMAND_NONE;
		passCount_ = 0;
		eventState_ = false;
		random_ = rand() % 7 + 1;
		commandCount_ = 0;

		for (int i = 0; i < 5; i++) {
			trueCommand_[i] = rand() % 4;
		}
	}
};

void Events::eventSet() {

	switch (commandState_)
	{
	case COMMAND_NONE:
		eventState_ = true;
		break;
	case COMMAND_PASS:
		if (passCount_ == 2) {
			eventState_ = false;
		} break;
	case COMMAND_FAIL:
		eventState_ = false;
		break;
	default:
		eventState_ = false;
		random_ = rand() % 7 + 1;
		break;
	}
}

void Events::showEvent() {
	
	if (eventState_) {
		// �̺�Ʈ ���� ���
		SDL_RenderCopy(g_renderer, events_texture_, &events_source_rect_[0], &events_destination_rect_[0]);
		SDL_RenderCopy(g_renderer, events_texture_, &events_source_rect_[random_], &events_destination_rect_[random_]);
		
		// Ŀ�ǵ� ���
		for (int i = 0; i < 5; i++) {
			SDL_RenderCopy(g_renderer, command_texture_, &command_source_rect_[trueCommand_[i]], &command_destination_rect_[i]);
			for (int j = 0; j < commandCount_; j++) {	// Ŀ�ǵ� ������ �ʷϻ����� �ٲ�
				SDL_RenderCopy(g_renderer, command_texture_green_, &command_source_rect_[trueCommand_[j]], &command_destination_rect_[j]);
			}
		}
	}
	if (passCount_ == 2) {
		SDL_Rect tmp_r;
		tmp_r = { 400, 200, output_rect_.w, output_rect_.h };
		SDL_RenderCopy(g_renderer, output_texture_[0], &output_rect_, &tmp_r);
	}
	else if (commandState_ == COMMAND_FAIL) {
		SDL_Rect tmp_r;
		tmp_r = { 400, 200, output_rect_.w, output_rect_.h };
		SDL_RenderCopy(g_renderer, output_texture_[1], &output_rect_, &tmp_r);
	}
}

void Events::compareCommand() {

	if (command_[commandCount_] == trueCommand_[commandCount_]) 
	{
		if (commandCount_ == 4) {
			commandState_ = COMMAND_PASS;
			commandCount_ = 0;
			passCount_++;
			for (int i = 0; i < 5; i++) {
				trueCommand_[i] = rand() % 4;
			}
		}
		else {
			commandCount_++; 
		}
	}
	else{
		commandState_ = COMMAND_FAIL;
		commandCount_ = 0;
	}
}

void Events::commandHandel() {

	SDL_Event event;

	if (eventState_ && SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				g_flag_running = false;
				break;

			case SDL_KEYDOWN:
				if (commandCount_ < 5) {
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
						command_[commandCount_] = 0;
						compareCommand(); break;
					case SDLK_s:
						command_[commandCount_] = 2;
						compareCommand(); break;
					case SDLK_a:
						command_[commandCount_] = 1;
						compareCommand(); break;
					case SDLK_d:
						command_[commandCount_] = 3;
						compareCommand(); break;
					default: break;
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:

				// If the mouse left button is pressed. 
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					g_current_game_phase = PHASE_ENDING;
				}
				else if (event.button.button == SDL_BUTTON_RIGHT)
				{
					g_current_game_phase = PHASE_ENDING;
				}
				break;

			default:
				break;
			}
		}
}

int Events::getPassOrFail() {
	// fail = 0, pass = 1, none = 2
	return commandState_;
}

bool Events::getEventState() {
	return eventState_;
}