WITH cheese_pizza AS 
	(SELECT m.pizza_name, po.person_id AS person_id
	FROM menu m
	JOIN person_order po ON po.menu_id = m.id
	GROUP BY  m.pizza_name, po.person_id 
	HAVING m.pizza_name LIKE 'cheese%' 
	),
	pepperoni_pizza AS 
	(SELECT  m.pizza_name, po.person_id AS person_id
	FROM menu m
	JOIN person_order po ON po.menu_id = m.id
	GROUP BY  m.pizza_name, po.person_id 
	HAVING m.pizza_name LIKE 'pepper%'
	)
SELECT  name
FROM person p
JOIN cheese_pizza ch
ON ch.person_id = p.id 
JOIN pepperoni_pizza pep
ON pep.person_id = p.id
WHERE p.gender = 'female'
ORDER BY name ASC;

