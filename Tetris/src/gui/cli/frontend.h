#ifndef FRONTEND_H
#define FRONTEND_H
/**
 * @file frontend.h
 * @brief Главный заголовочный файл для фронтенда игры Тетрис (отрисовки)
 * @author solanged
 * @date 2025
 *
 * Содержит все объявления функций для отрисовки игры
 */
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "../../brick_game/tetris/api.h"

#define FIELD_WIDTH 10   ///< Ширина игрового поля в клетках
#define FIELD_HEIGHT 20  ///< Высота игрового поля в клетках

/**
 * @brief Отрисовывает игровое поле и интерфейс
 * @param game_info Структура с информацией об игре для отрисовки
 */
void drawField(GameInfo_t game_info);

/**
 * @brief Проверяет, находится ли игра в начальном состоянии
 * @param game_info Структура с информацией об игре
 * @return true если игра в начальном состоянии, false в противном случае
 */
bool isInitStateOfGame(GameInfo_t game_info);

/**
 * @brief Проверяет, завершена ли игра
 * @param game_info Структура с информацией об игре
 * @param last_blocked_time Указатель на время последней блокировки
 * @return true если игра завершена, false в противном случае
 */
bool isGameOver(GameInfo_t game_info, clock_t *last_blocked_time);

/**
 * @brief Получает высоту следующего тетромино
 * @param game_info Структура с информацией об игре
 * @return Высота следующего тетромино в клетках
 */
int getNextTetraminoHight(GameInfo_t game_info);

/**
 * @brief Отрисовывает панель следующего тетромино
 * @param game_info Структура с информацией об игре
 */
void drawNext(GameInfo_t game_info);

/**
 * @brief Отрисовывает блок с информацией (счет, уровень, скорость)
 * @param game_info Структура с информацией об игре
 */
void drawInformationBlock(GameInfo_t game_info);

/**
 * @brief Проверяет, пустая ли указанная линия на игровом поле
 * @param game_info Структура с информацией об игре
 * @param line Номер линии для проверки
 * @return true если линия пустая, false в противном случае
 */
bool isLineEmpty(GameInfo_t game_info, int line);

/**
 * @brief Главный игровой цикл
 *
 * Управляет основным циклом игры, обработкой ввода, обновлением состояния
 * и отрисовкой игрового поля.
 */
void gameLoop();

#endif /* FRONTEND_H */