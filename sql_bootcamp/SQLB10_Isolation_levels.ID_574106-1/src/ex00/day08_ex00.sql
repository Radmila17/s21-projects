-- Session #1
BEGIN; -- start transaction
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut'; -- update rating
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- check changes in session 1
COMMIT; -- commit changes

-- Session #2  
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- check changes in session 2 (before commit)
SELECT * FROM pizzeria WHERE name = 'Pizza Hut'; -- check changes in session 2 (after commit)