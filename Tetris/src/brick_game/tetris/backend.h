#ifndef BACKEND_H
#define BACKEND_H
/**
 * @file backend.h
 * @brief Главный заголовочный файл для бэкенд логики игры Тетрис
 * @author solanged
 * @date 2025
 *
 * Содержит все структуры, перечисления и объявления функций для бэкенда игры
 * Тетрис, включая управление состоянием игры, операции с тетромино и
 * обнаружение столкновений.
 */
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "api.h"

#define START_BUTTON 115     ///< Клавиша 's' для начала игры
#define PAUSE_BUTTON 112     ///< Клавиша 'p' для паузы игры
#define TERMINATE_BUTTON 27  ///< Клавиша ESC для завершения игры
#define KEY_LEFT 0404        ///< Код клавиши стрелка влево
#define KEY_RIGHT 0405       ///< Код клавиши стрелка вправо
#define KEY_UP 403           ///< Код клавиши стрелка вверх
#define KEY_DOWN 0402        ///< Код клавиши стрелка вниз
#define ERR -1               ///< Код ошибки
#define OK 0                 ///< Код успеха
#define FPS 60.0             ///< Кадров в секунду для игрового цикла

#define ACTION_BUTTON 32  ///< Пробел для специального действия
#define FIELD_HEIGHT 20   ///< Высота игрового поля в клетках
#define FIELD_WIDTH 10    ///< Ширина игрового поля в клетках
#define TETRAMINO_SIZE 4  ///< Размер матрицы тетромино (4x4)

/**
 * @brief Перечисление типов тетромино
 */
typedef enum {
  I,  ///< I-образное тетромино
  L,  ///< L-образное тетромино
  J,  ///< J-образное тетромино
  O,  ///< O-образное тетромино
  S,  ///< S-образное тетромино
  T,  ///< T-образное тетромино
  Z   ///< Z-образное тетромино
} TetraminoType_t;

/**
 * @brief Структура, представляющая текущее тетромино
 */
typedef struct {
  int x_coord;                 ///< X-координата на игровом поле
  int y_coord;                 ///< Y-координата на игровом поле
  int **field;                 ///< Матрица 4x4, в которой находится тетрамино
  TetraminoType_t piece_type;  ///< Тип тетромино
} CurrentTetramino_t;

/**
 * @brief Состояния конечного автомата для игровой логики
 */
typedef enum {
  Init = 0,   ///< Начальное состояние - отрисовка поля и подготовка к появлению
  Spawn,      ///< Состояние появления нового тетромино
  Moving,     ///< Состояние движения - обработка пользовательского ввода
  Shifting,   ///< Состояние падения - тетромино движется вниз
  Attaching,  ///< Состояние прикрепления
  OnPause,    ///< Состояние паузы - игра приостановлена
  GameOver,   ///< Состояние завершения игры
} FSM_t;

/**
 * @brief Полная структура информации об игре для бэкенда
 */
typedef struct {
  GameInfo_t *game_info;             ///< Базовая информация об игре
  FSM_t fsm_state;                   ///< Текущее состояние конечного автомата
  CurrentTetramino_t cur_tetramino;  ///< Текущее движущееся тетромино
  clock_t time_stamp;                ///< Метка времени для игрового тайминга
  TetraminoType_t next_piece_type;   ///< Тип следующего тетромино
} FullGameInfo_t;

/**
 * @brief Структура для отслеживания заполненных рядов
 */
typedef struct {
  int array[20];  ///< Массив индексов заполненных рядов
  int count;      ///< Количество заполненных рядов
} FilledRows_t;

/** @brief Тип указателя на функцию для функций игрового состояния */
typedef void (*GameFunc)(FullGameInfo_t *full_game_info);

// Операции с матрицами
/**
 * @brief Копирует следующее тетромино в текущее тетромино
 * @param full_game_info Указатель на структуру полной информации об игре
 */
void copyNextToCurrentTetramino(FullGameInfo_t *full_game_info);

/**
 * @brief Заполняет матрицу нулями
 * @param rows Количество строк в матрице
 * @param columns Количество столбцов в матрице
 * @param matrix Указатель на матрицу для инициализации
 */
void fillMatrixWithZeros(int rows, int columns, int ***matrix);

// Инициализация игры
/**
 * @brief Инициализирует структуру полной информации об игре
 * @param full_game_info Указатель на существующую структуру или NULL для нового
 * выделения
 * @return Указатель на инициализированную структуру FullGameInfo_t
 */
FullGameInfo_t *initializeFullGameInfo(FullGameInfo_t *full_game_info);

/**
 * @brief Инициализирует базовую структуру информации об игре
 * @param game_info Указатель на существующую структуру или NULL для нового
 * выделения
 * @return Указатель на инициализированную структуру GameInfo_t
 */
GameInfo_t *initGameInfo(GameInfo_t *game_info);

// Обработка ввода
/**
 * @brief Обрабатывает действие пользовательского ввода
 * @param action Действие пользователя для обработки
 * @param hold Является ли действие действием удержания
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Проверяет заполненные ряды на игровом поле
 * @param filled_rows Структура для хранения индексов заполненных рядов
 * @param full_game_info Структура информации об игре
 * @return true если найдены заполненные ряды, false в противном случае
 */
bool checkFilledRows(FilledRows_t *filled_rows, FullGameInfo_t full_game_info);

// Функции игрового состояния
/**
 * @brief Создает новое тетромино
 * @param full_game_info Структура информации об игре
 */
void spawn(FullGameInfo_t *full_game_info);

/**
 * @brief Сдвигает текущее тетромино вниз на один ряд
 * @param full_game_info Структура информации об игре
 */
void shiftDown(FullGameInfo_t *full_game_info);

/**
 * @brief Удаляет заполненные ряды, обновляет счет, скорость и уровень
 * @param full_game_info Структура информации об игре
 * @param filled_rows Структура, содержащая индексы заполненных рядов
 */
void removeFilledRows(FullGameInfo_t *full_game_info, FilledRows_t filled_rows);

/**
 * @brief Прикрепляет текущее тетромино к игровому полю и проверяет на наличие
 * заполненых рядов
 * @param full_game_info Структура информации об игре
 */
void attach(FullGameInfo_t *full_game_info);

/**
 * @brief Размещает текущее тетромино на игровом поле
 * @param full_game_info Структура информации об игре
 */
void placeTetraminoOnField(FullGameInfo_t *full_game_info);

/**
 * @brief Проверяет столкновение по указанным координатам
 * @param full_game_info Структура информации об игре
 * @param x_coord X-координата для проверки
 * @param y_coордината Y-координата для проверки
 * @return 1 если обнаружено столкновение, 0 в противном случае
 */
int checkCollision(FullGameInfo_t full_game_info, int x_coord, int y_coord);

// Управление игрой
/**
 * @brief Завершает игру и очищает память
 * @param full_game_info Структура информации об игре
 */
void terminateGame(FullGameInfo_t *full_game_info);

/**
 * @brief Ставит игру на паузу или наоборот возобновляет игру
 * @param full_game_info Структура информации об игре
 */
void pauseGame(FullGameInfo_t *full_game_info);

/**
 * @brief Удаляет и освобождает память матрицы
 * @param matrix Указатель на матрицу для удаления
 * @param rows Количество строк в матрице
 */
void removeMatrix(int ***matrix, int rows);

// Операции с тетромино
/**
 * @brief Создает следующее тетромино и сохраняет его в game_info->next
 * @param game_info Структура информации об игре
 * @return Тип созданного тетромино
 */
TetraminoType_t createNextTetramino(GameInfo_t *game_info);

/**
 * @brief Выделяет память для матрицы
 * @param rows Количество строк
 * @param columns Количество столбцов
 * @param result Указатель для хранения выделенной матрицы
 * @return OK при успехе, ERR при неудаче
 */
int allocateMatrix(int rows, int columns, int ***result);

/**
 * @brief Получает текущую полную информацию об игре
 * @param current_full_game_info Текущая информация об игре или NULL для
 * глобального экземпляра
 * @return Статический указатель на структуру полной информации об игре
 */
FullGameInfo_t *getFullGameInfo(FullGameInfo_t *current_full_game_info);

/**
 * @brief Вращает фигуру тетромино внутри матрицы текущего тетрамино
 * @param full_game_info Структура информации об игре
 * @param clockwise Направление вращения (по часовой стрелке)
 * @param temp_matrix Временная матрица для вычислений вращения
 */
void rotateFigure(FullGameInfo_t *full_game_info, bool clockwise,
                  int **temp_matrix);

/**
 * @brief Вращает тетрамино на главном поле игры
 * @param full_game_info Структура информации об игре
 */
void rotate(FullGameInfo_t *full_game_info);

/**
 * @brief Двигает текущее тетромино вправо
 * @param full_game_info Структура информации об игре
 */
void moveRight(FullGameInfo_t *full_game_info);

/**
 * @brief Двигает текущее тетромино влево
 * @param full_game_info Структура информации об игре
 */
void moveLeft(FullGameInfo_t *full_game_info);

// Вспомогательные функции
/**
 * @brief Очищает след тетромино от предыдущей позиции
 * @param full_game_info Структура информации об игре
 * @param prev_x Предыдущая X-координата
 * @param prev_y Предыдущая Y-координата
 */
void clearTetraminoTrail(FullGameInfo_t *full_game_info, int prev_x,
                         int prev_y);

/**
 * @brief Двигает тетрамино вниз по истечению определнного промежутка времени,
 * зависящего от скорости падения тетрамино
 */
void shift();

/**
 * @brief Проверяет, «соприкосновение» текущего блока с уже упавшими или с
 * землей
 * @param full_game_info Структура информации об игре
 * @return 1 если может соприкасается, 0 в противном случае
 */
int checkAttaching(FullGameInfo_t full_game_info);

/**
 * @brief Инициализирует новое игровое состояние
 * @param full_game_info Структура информации об игре
 */
void initNewGame(FullGameInfo_t *full_game_info);

/**
 * @brief Сдвигает тетрамино в левый угол своего поля после вращения
 * @param full_game_info Структура информации об игре
 */
void normilizeTetraminoOffset(FullGameInfo_t *full_game_info);

/**
 * @brief Вычисляет интервал падения на основе уровня игры
 * @param full_game_info Структура информации об игре
 * @return Интервал падения в секундах
 */
double calculateFallInterval(FullGameInfo_t *full_game_info);

// Операции со счетом
/**
 * @brief Проверяет и возвращает рекордный счет
 * @return Текущий рекордный счет
 */
int checkHightScore();

/**
 * @brief Записывает рекордный счет в хранилище
 * @param game_info Структура информации об игре
 */
void writeHightScore(GameInfo_t *game_info);

#endif /* BACKEND_H */