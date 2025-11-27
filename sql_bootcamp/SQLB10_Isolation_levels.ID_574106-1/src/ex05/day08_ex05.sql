-- Сессия №1
-- Начинаем транзакцию сессии №1 с уровнем изоляции READ COMMITTED
BEGIN ISOLATION LEVEL READ COMMITTED;
-- Сессия №2, начинаем транзакцию сессии №2 с уровнем изоляции READ COMMITTED
-- BEGIN ISOLATION LEVEL READ COMMITTED;

-- Суммируем все рейтинги пиццерий в транзакции сессии №1 (первое чтение)
SELECT SUM(rating) FROM pizzeria;
-- Вставляем новую пиццерию 'Kazan Pizza' в транзакции сессии №2
-- INSERT INTO pizzeria (id, name, rating) VALUES (10, 'Kazan Pizza', 5);
-- Фиксируем изменения в транзакции сессии 2
-- COMMIT;

-- Снова суммируем все рейтинги пиццерий в транзакции сессии №1 (второе чтение)
SELECT SUM(rating) FROM pizzeria;
-- Фиксируем изменения в транзакции сессии 1
COMMIT;

-- Проверяем итоговую сумму рейтингов в сессии 1
SELECT SUM(rating) FROM pizzeria;

-- Сессия №2 (после завершения сессии 1)
-- BEGIN ISOLATION LEVEL READ COMMITTED;

-- INSERT INTO pizzeria (id, name, rating) VALUES (10, 'Kazan Pizza', 5);

-- COMMIT;

-- SELECT SUM(rating) FROM pizzeria;