SELECT piz.name, count(*) AS count_of_orders, round(avg(m.price), 2) AS average_price, max(m.price) AS max_price, min(m.price) AS min_price
FROM person_order po
JOIN menu m ON m.id = po.menu_id
JOIN pizzeria piz ON m.pizzeria_id = piz.id
GROUP BY piz.name
ORDER BY piz.name;