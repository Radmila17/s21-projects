-- Сессия №1
-- Начинаем транзакцию сессии №1 с уровнем изоляции REPEATABLE READ
BEGIN ISOLATION LEVEL REPEATABLE READ;
-- Сессия №2, начинаем транзакцию сессии №2 с уровнем изоляции REPEATABLE READ
-- BEGIN ISOLATION LEVEL REPEATABLE READ;

-- Проверяем текущий рейтинг в транзакции сессии №1
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Проверяем текущий рейтинг в транзакции сессии №2
-- SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- Обновляем рейтинг на 4 в транзакции сессии №1
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut';
-- Обновляем рейтинг на 3.6 в транзакции сессии №2
-- UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
-- Появилось сообщение об ошибке 
-- ERROR:  could not serialize access due to concurrent update


-- Фиксируем изменения в транзакции сессии 1
COMMIT;
-- Фиксируем изменения в транзакции сессии 2
-- COMMIT;
-- Вместо COMMIT программа совершила ROLLBACK

-- Проверяем итоговый рейтинг в сессиях
SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';
-- Результат 4. Особенность REPEATABLE READ: При попытке обновить одну и ту же строку 
-- в двух параллельных транзакциях вторая получит ошибку сериализации.

-- Сессия №2
-- BEGIN ISOLATION LEVEL REPEATABLE READ;

-- SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';

-- UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';

-- COMMIT;

-- SELECT rating FROM pizzeria WHERE name = 'Pizza Hut';