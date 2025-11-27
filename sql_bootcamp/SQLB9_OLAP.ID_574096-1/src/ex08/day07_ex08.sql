SELECT p.address,piz.name, count(*) AS count_of_orders
FROM person p
JOIN person_order po ON po.person_id = p.id 
JOIN menu m ON m.id = po.menu_id 
JOIN pizzeria piz ON piz.id = m.pizzeria_id 
GROUP BY p.address,piz.name
ORDER BY p.address,piz.name;