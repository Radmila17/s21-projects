SELECT m.pizza_name,
	m.price,
	piz.name AS pizzeria_name
FROM menu m
LEFT JOIN person_order po ON po.menu_id = m.id
JOIN pizzeria piz ON piz.id = m.pizzeria_id 
WHERE po.id IS NULL 
ORDER BY m.pizza_name, m.price;