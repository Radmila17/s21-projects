WITH pizzas_names AS 
	(SELECT m.pizza_name, m.price, count(*)
	FROM menu m 
	JOIN pizzeria piz ON m.pizzeria_id = piz.id 
	GROUP BY m.pizza_name, m.price
	HAVING count(*)>1)
SELECT pn.pizza_name, piz1.name AS p1_name, piz2.name AS p2_name, pn.price 
FROM pizzas_names pn 
JOIN menu m ON m.pizza_name = pn.pizza_name AND pn.price = m.price 
JOIN pizzeria piz1 ON piz1.id = m.pizzeria_id
JOIN menu m2 ON m2.pizza_name = pn.pizza_name  AND pn.price = m2.price AND m.id > m2.id 
JOIN pizzeria piz2 ON piz2.id = m2.pizzeria_id
ORDER BY pizza_name;

-- более простой вариант, до которого я не додумалась сразу
SELECT 
    m1.pizza_name,
    p1.name AS pizzeria_name_1,
    p2.name AS pizzeria_name_2,
    m1.price
FROM menu m1
JOIN menu m2 ON m1.pizza_name = m2.pizza_name 
    AND m1.price = m2.price 
    AND m1.pizzeria_id > m2.pizzeria_id
JOIN pizzeria p1 ON m1.pizzeria_id = p1.id
JOIN pizzeria p2 ON m2.pizzeria_id = p2.id
ORDER BY m1.pizza_name;