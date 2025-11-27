-- Сессия №1
-- Начинаем транзакцию сессии №1
BEGIN;
-- Сессия №2, начинаем транзакцию сессии №2
-- BEGIN;
-- Проверяем текущий рейтинг в транзакции сессии №1
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Проверяем текущий рейтинг в транзакции сессии №2
-- SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- Обновляем рейтинг на 4 в транзакции сессии №1
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut';
-- Обновляем рейтинг на 3.6 в транзакции сессии №2
-- UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';

-- Фиксируем изменения в транзакции сессии 1
COMMIT;
-- Фиксируем изменения в транзакции сессии 2
-- COMMIT;

-- Проверяем итоговый рейтинг в транзакции сессии 1 и транзакции сессии 2
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- Сессия № 2
BEGIN;

SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';

COMMIT;

SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';


-- Результат 3.6, обновления первой сессии не применились и потерялись
