SELECT
	object_name
FROM 
	(SELECT m.pizza_name AS object_name,
		2 AS source_order
	FROM
		menu m
	UNION ALL
	SELECT
		p."name" AS object_name,
		1 AS source_order
	FROM
		person p) AS combined
ORDER BY
	object_name, combined.source_order ASC;