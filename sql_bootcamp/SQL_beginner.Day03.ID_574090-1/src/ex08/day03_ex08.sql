INSERT INTO menu
VALUES((SELECT max(id) FROM menu)+1,(SELECT id FROM pizzeria AS piz WHERE piz.name = 'Dominos'), 'Sicilian pizza',  900);
SELECT * FROM menu;


SELECT count(*) = 1 AS CHECK
 FROM menu
 WHERE id = 21
   AND pizzeria_id = 2
   AND pizza_name = 'Sicilian pizza'
   AND price = 900