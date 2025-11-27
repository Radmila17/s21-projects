-- Сессия №1
-- Начинаем транзакцию сессии №1 с уровнем изоляции REPEATABLE READ
BEGIN ISOLATION LEVEL REPEATABLE READ;
-- Сессия №2, начинаем транзакцию сессии №2 с уровнем изоляции REPEATABLE READ
-- BEGIN ISOLATION LEVEL REPEATABLE READ;

-- Суммируем все рейтинги пиццерий в транзакции сессии №1 (первое чтение)
SELECT SUM(rating) FROM pizzeria;
-- Результат 26.9


-- Вставляем новую пиццерию 'Kazan Pizza 2' в транзакции сессии №2
-- INSERT INTO pizzeria (id, name, rating) VALUES (11, 'Kazan Pizza 2', 4);
-- Фиксируем изменения в транзакции сессии 2
-- COMMIT;

-- Снова суммируем все рейтинги пиццерий в транзакции сессии №1 (второе чтение)
SELECT SUM(rating) FROM pizzeria;
-- Результат 26.9

-- Фиксируем изменения в транзакции сессии 1
COMMIT;

-- Проверяем итоговую сумму рейтингов в сессии 1
SELECT SUM(rating) FROM pizzeria;

-- Результат 30.9


-- Сессия №2 (после завершения сессии 1)
-- BEGIN ISOLATION LEVEL REPEATABLE READ;

-- INSERT INTO pizzeria (id, name, rating) VALUES (11, 'Kazan Pizza 2', 4);

-- COMMIT;

-- SELECT SUM(rating) FROM pizzeria;