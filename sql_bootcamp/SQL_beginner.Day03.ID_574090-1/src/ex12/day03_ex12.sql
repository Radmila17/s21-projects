INSERT INTO person_order 
SELECT 
	(SELECT max(id) FROM person_order)+ gs,
    p.id,
    (SELECT id FROM menu WHERE pizza_name = 'greek pizza'),
    '2022-02-25'
FROM person p,  generate_series(1, (SELECT count(*) FROM person)) AS gs
WHERE 
  p.id = gs;
SELECT * FROM person_order po;

SELECT count(*) = 9 AS CHECK
 FROM person_order
 WHERE order_date = '2022-02-25'
   AND menu_id =
     (SELECT id
     FROM menu
     WHERE pizza_name = 'greek pizza')
     