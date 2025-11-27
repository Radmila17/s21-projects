CREATE UNIQUE INDEX IF NOT EXISTS idx_menu_unique 
ON menu(pizzeria_id, pizza_name);

EXPLAIN ANALYZE
SELECT pizza_name FROM menu 
WHERE pizzeria_id = 1 AND pizza_name = 'cheese pizza';

SET enable_seqscan = OFF;

EXPLAIN ANALYZE
SELECT pizza_name FROM menu 
WHERE pizzeria_id = 1 AND pizza_name = 'cheese pizza';

SET enable_seqscan = On;

--INSERT INTO menu (id, pizzeria_id, pizza_name, price) 
--VALUES (21, 1, 'cheese pizza', 900);