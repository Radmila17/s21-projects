UPDATE menu
SET price = (SELECT price FROM menu m WHERE m.pizza_name = 'greek pizza')*0.9
WHERE pizza_name = 'greek pizza';
SELECT * FROM menu;

SELECT (800-800*0.1) = price AS CHECK
 FROM menu
 WHERE pizza_name = 'greek pizza'