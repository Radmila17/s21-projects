-- Сессия №1
-- Начинаем транзакцию сессии №1 с уровнем изоляции SERIALIZABLE
BEGIN ISOLATION LEVEL SERIALIZABLE;
-- Сессия №2, начинаем транзакцию сессии №2 с уровнем изоляции SERIALIZABLE
-- BEGIN ISOLATION LEVEL SERIALIZABLE;

-- Проверяем текущий рейтинг в транзакции сессии №1 (первое чтение)
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Результат 3.6
-- Обновляем рейтинг на 3.0 в транзакции сессии №2
-- UPDATE pizzeria SET rating = 3.0 WHERE name = 'Pizza Hut';
-- Фиксируем изменения в транзакции сессии 2
-- COMMIT;

-- Проверяем текущий рейтинг в транзакции сессии №1 (второе чтение)
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Результат все ещё 3.6
-- Фиксируем изменения в транзакции сессии 1
COMMIT;

-- Проверяем итоговый рейтинг в сессии 1
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Результат уже 3.0

-- Сессия №2
-- BEGIN ISOLATION LEVEL SERIALIZABLE;

-- UPDATE pizzeria SET rating = 3.0 WHERE name = 'Pizza Hut';

-- COMMIT;

-- SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- Результат 3.0