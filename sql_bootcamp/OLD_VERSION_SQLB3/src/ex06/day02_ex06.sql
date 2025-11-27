SELECT m.pizza_name AS pizza_name, piz.name AS pizzeria_name
FROM menu m 
JOIN pizzeria piz ON piz.id = m.pizzeria_id 
JOIN person_order po ON po.menu_id = m.id 
JOIN person p ON p.id = po.person_id AND (p."name" = 'Denis' OR p."name" = 'Anna')
ORDER BY pizza_name , pizzeria_name;