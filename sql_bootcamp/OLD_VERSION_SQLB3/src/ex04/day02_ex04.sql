WITH m AS 
(SELECT m.pizza_name, m.price, m.pizzeria_id  FROM menu m WHERE m.pizza_name LIKE 'mushro%' OR m.pizza_name LIKE 'peppero%')
SELECT m.pizza_name , piz.name AS pizzeria_name, price
FROM m 
JOIN pizzeria piz ON piz.id =m.pizzeria_id
ORDER BY pizza_name, pizzeria_name;