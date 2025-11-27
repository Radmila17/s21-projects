SELECT
	m.id AS object_id ,
	m.pizza_name AS object_name
FROM
	menu m
UNION ALL 
SELECT
	p.id AS object_id ,
	p."name" AS object_name
FROM
	person p
ORDER BY
	object_id,
	object_name ASC;