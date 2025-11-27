WITH p AS 
	(SELECT * 
	FROM person p
	WHERE (p.address LIKE 'Mos%' OR p.address LIKE 'Samara' ) AND p.gender LIKE 'male')
SELECT name 
FROM p
JOIN person_order po ON po.person_id = p.id
JOIN menu m ON m.id = po.menu_id AND (m.pizza_name LIKE 'pepper%' OR  m.pizza_name LIKE 'mush%')
ORDER BY name DESC;