
DELETE FROM person_order 
WHERE order_date = '2022-02-25';
SELECT * FROM person_order;
DELETE FROM menu
WHERE pizza_name = 'greek pizza';
SELECT * FROM menu;

--In a lower case letter
UPDATE menu
SET pizza_name = 'sicilian pizza'
WHERE pizza_name = 'Sicillian pizza';

SELECT * FROM menu;
SELECT * FROM person_order;
SELECT * FROM person_visits pv;