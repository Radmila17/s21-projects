-- Сессия №1
-- Начинаем транзакцию сессии №1 с уровнем изоляции READ COMMITTED
BEGIN ISOLATION LEVEL READ COMMITTED;
-- Сессия №2, начинаем транзакцию сессии №2 с уровнем изоляции READ COMMITTED
-- BEGIN ISOLATION LEVEL READ COMMITTED;

-- Проверяем текущий рейтинг в транзакции сессии №1 (первое чтение)
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Обновляем рейтинг на 3.6 в транзакции сессии №2
-- UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
-- Фиксируем изменения в транзакции сессии 2
-- COMMIT;

-- Проверяем текущий рейтинг в транзакции сессии №1 (второе чтение - здесь будет Non-Repeatable Read)
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
-- Фиксируем изменения в транзакции сессии 1
COMMIT;

-- Проверяем итоговый рейтинг в сессии 1
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- Сессия №2 
-- BEGIN ISOLATION LEVEL READ COMMITTED;

-- UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';

-- COMMIT;

-- SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';