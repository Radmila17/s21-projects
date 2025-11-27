INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT
	ROW_NUMBER()  OVER () AS id,
	person_id,
    pizzeria_id,
    CASE 
        WHEN order_count = 1 THEN 10.5
        WHEN order_count = 2 THEN 22
        ELSE 30
    END AS discount
FROM (
	SELECT person_id, pizzeria_id, count(*) AS order_count
	FROM person_order po 
	JOIN menu m ON po.menu_id = m.id
	GROUP BY person_id, pizzeria_id
) AS order_counts;

SELECT * FROM person_discounts;

SELECT count(*) > 0 AS check
FROM person_discounts