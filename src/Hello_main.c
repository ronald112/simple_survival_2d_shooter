#include "header.h"

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;
	
	wait = 16 + *remainder;
	
	*remainder -= (int)*remainder;
	
	frameTime = SDL_GetTicks() - *then;
	
	wait -= frameTime;
	
	if (wait < 1)
	{
		wait = 1;
	}
		
	SDL_Delay(wait);
	
	*remainder += 0.667;
	
	*then = SDL_GetTicks();
}

int main() {
    t_app app;
    t_entity player;
    SDL_Rect dest;
    t_sounds sound;
    t_stage stage;

    memset(&app, 0, sizeof(app));
    memset(&player, 0, sizeof(player));  
    
    init_SDL(&app);
    
    // player.x = 100;
    // player.y = 100;
    
    init_stage(&player, &stage, &app);
    
    // sounds
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);	
    sound.main_menu_music = Mix_LoadMUS("resource/Audio/Music/ElectroHouse.mp3");
	sound.cave_background_sounds = Mix_LoadWAV("resource/Audio/Sounds/Background/Cave.wav");
	sound.steps_sounds = Mix_LoadWAV("resource/Audio/Sounds/Footsteps_on_sand.wav");
    Mix_PlayMusic(sound.main_menu_music, -1);
	Mix_VolumeMusic(5);
	//Mix_PlayChannel(6, cave_background_sounds, -1);
	Mix_VolumeChunk(sound.cave_background_sounds, 50);

    long then = SDL_GetTicks();	
	float remainder = 0;

    while (1) {
        prepare_scene(&app, &dest);
        do_input(&app, sound.steps_sounds, &player);
        SDL_GetMouseState(&app.mouse.x, &app.mouse.y);

        logic(&stage, &player, &app);

        if (app.up && player.y > 7)	{
			// change lookup
			player.y -= 4;
		}
		
		if (app.down && player.y < SCREEN_HEIGHT - 50) {
			// change lookdown
			player.y += 4;
		}
		
		if (app.left && player.x > 7) {
			// change lookleft
			player.x -= 4;
		}
		
		if (app.right && player.x < SCREEN_WIDTH - 50) {
			 // change lookright
			player.x += 4;
		}

        
        draw(&player, &stage, &app);
        present_scene(&app);
        capFrameRate(&then, &remainder);
    }
    Mix_FreeMusic(sound.main_menu_music);
	Mix_FreeChunk(sound.cave_background_sounds);
	Mix_FreeChunk(sound.steps_sounds);
	Mix_CloseAudio();

    cleanup(&app);

    return 0;
}







/*
SDL_Init - функція використовується для иніціалізації бібліотеки SDL (більшості його функцій). Зачасту повинна бути визвана перед більшістю функцій SDL. Повертає 0 коли все пройшло добре і мінусові значення, коли виникла помилка. Прикл. SDL_Init(SDL_INIT_VIDEO).
SDL_Quit - Функція для очистки (завершення) усіх иніціалізованих підсистем (напр. SDL_Window).
//
SDL_Event - функція, яка містить в собі структури для різних типів подій. Завдяки неї можна відслідковувати бажані події (напр. натискання клавіші, рух курсора миші і тд.)
Наприклад: SDL_Event event; event.type == SDL_KEYDOWN; - перевірка на натискання клавіші
//
SDL_PoliEvent - функція приймає вказівник на структуру SDL_Event, щоб записати в неї інформацію про подію. Якщо ніяких подій немає, то повертає 0, інакше 1. Наприклад - SDL_PoliEvent(&test_event)
Функция SDL_PollEvent () получает указатель на структуру SDL_Event, которая должна быть 
заполнена информацией о событии. Мы знаем , что если SDL_PollEvent () 
удаляет событие из очереди , то информация о событии будет размещена в нашей структуре 
test_event, но мы также знаем , что тип события будет помещен в типе члене test_event. 
Поэтому для обработки каждого типа события отдельно мы используем оператор switch .
//
SDL_Window *name - тут ми у вказівник задаємо наше вікно, яке ми створимо.
SDL_CreateWindow - функція, яка створює нове вікно з вказаною: позицією, розміром та флагами.
Наприклад: SDL_Window *window = SDL_CreateWindow ("Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

SDL_Renderer *renderer - використовується для запису рендерінга у вказівник, щоб потім через нього взаємодіяти з рендерінгом.
        =
SDL_CreateRenderer - функція для створення 2д контекста та 2д рендерінга вікна.
SDL_CreateRenderer(name_of_window, index (-1 deffault), name_of_render_Flags);

SDL_RenderClear - функція, яка очищає теперішню ціль рендеринга кольором, який ви вказали. Приймає вказівник - (renderer)
SDL_RenderPresent - функція, використовується для обновлення будь-якого рендерінга екрану, що виконано з часу минулого визова.
SDL_DestroyRenderer - функція, щоб видалити контекст рендерінга для вікна і звільнити пов*язані з ним текстури.
SDL_SetRenderDrawColor - функція для встановлення кольору для операцій малювання (Rect, Line та Clear). Наприклад: SDL_SetRenderDrawColor(вказівник на вікно, r, g, b, a).
SDL_RenderDrawPoint (до чого застосувати, x, y); - функція використовується для позначення точки на координатах певного кольору.
SDL_RenderDrawPoint (до чого застосувати, x1, y1, x2, y2); - функція використовується для позначення лінії певного кольору на координатах.
SDL_Rect назва = {x1, y1, x2, y2}; - функція для вимальовування квадрата певного кольору.
SDL_RenderFillRect (до чого застосувати, адреса квадрата); - функція вимальовує квадрат у потрібному місці.
SDL_RenderDrawRect (до чого застосувати, адреса квадрата); - функція вимальовує квадрат у потрібному місці (у кольорі лише окантовка).
SDL_Surface *name - функція, зберігає і собі набір пікселів. Використовується з IMG_Load("fileName.type")
//audio
SDL_Init(SDL_INIT_AUDIO); - ініціалізуємо аудіо системи
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); - функція для встановлення аудіо налаштувань та підготовки для підключення.
1 - частота в Гц, 2 - формат образу, 3 - кількість аудіопотоків (2 - стерео, 1 - моно), 4 - кількість байт для вихідної виборки.
Mix_Music *назва = Mix_LoadMUS("назва.формат"); - ці функції використовуються для підключення і збереження аудіо файлу в змінну.
Mix_Chunk *назва = Mix_LoadWav("назва.wav") - ці функції беруть аудіо файл типу .wav та зберігають у структуру. Mix_Chunk повертає 1, якщо пам*ять виділена та 0 якщо ні.
Mix_FreeMusic(name); - функція звільняє пам*ять та зупиняє відтворення цього звуку і блокує його до повної зупинки.
Mix_FreeChunk(name); - функція звільняє пам*ять з чанку і після цього не загружає в нього нових даних. (Не можна звільнити данні, які ще відтворюються).
Mix_CloseAudio(name); - функція виключає та очищає Api мікшера. Після виклику всі аудіо зупиняються, та функції мікшера перестають діяти. Щоб знову увімкнути - Mix_OpenAudio;
Mix_QuerySpec, щоб дізнатися, скільки разів Mix_CloseAudio необхідно викликати до того, як пристрій буде фактично закрито.
Mix_PlayMusic(nameOfAudio, кільк.відтворення); - функція запускає аудіо файл. В 1 - приймає вказівник на аудіо файл, а в 2 - кільк. виконання (-1 це вічно, 0 нуль разів, 1 один раз...). Повертає 0 коли все добре та -1 коли виникли помилки.
Mix_PlayChannel(channel, Mix_Chunk *name, loops); - функція відтворює чанк на каналі і якщо канал = -1, то обереться перший пустий канал. Кількість ітерацій завжди на 1 більше за вказану нами.
//
SDL_Delay(num is milliseconds) - зупиняє покальше виконання коду на вказану кількість часу.

*/


