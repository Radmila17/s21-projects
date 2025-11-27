SELECT m.pizza_name,
	m.price,
	piz.name AS pizzeria_name,
	pv.visit_date 
FROM menu m
JOIN pizzeria piz ON piz.id = m.pizzeria_id 
JOIN person_visits pv ON pv.pizzeria_id = m.pizzeria_id 
JOIN person p ON p.id = pv.person_id 
WHERE p."name" = 'Kate' AND m.price BETWEEN 800 AND 1000
ORDER BY pizza_name, price, pizzeria_name;