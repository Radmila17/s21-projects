-- Сессия №1
-- Начинаем транзакцию
BEGIN;
-- Сессия №2, начинаем транзакцию
-- BEGIN;

-- Обновляем пиццерию с id=1 в сессии №1
UPDATE pizzeria SET rating = 1 WHERE id = 1;
-- Обновляем пиццерию с id=2 в сессии №2
-- UPDATE pizzeria SET rating = 2 WHERE id = 2;

-- Пытаемся обновить пиццерию с id=2 в сессии №1 (будет ждать сессию №2)
UPDATE pizzeria SET rating = 3 WHERE id = 2;
-- Пытаемся обновить пиццерию с id=1 в сессии №2 (будет ждать сессию №1) - DEADLOCK!
-- UPDATE pizzeria SET rating = 4 WHERE id = 1;

-- Возникает ошибка 
-- ERROR:  deadlock detected
-- Коммитим в сессии 1
COMMIT;

-- Коммитим в сессии 2
-- COMMIT;
-- Вместо коммита произошел ROLLBACK, то есть откат измененийэтой сессии.


-- Вывод: применились изменения только первой сессии.

/*
postgres=# select * from pizzeria;
 id |     name      | rating 
----+---------------+--------
  3 | DoDo Pizza    |    3.2
  4 | Papa Johns    |    4.9
  5 | Best Pizza    |    2.3
  6 | DinoPizza     |    4.2
 10 | Kazan Pizza   |      5
 11 | Kazan Pizza 2 |      4
  1 | Pizza Hut     |      1
  2 | Dominos       |      3
(8 rows)

*/