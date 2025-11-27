SELECT p.name AS person_name, m.pizza_name, m.price, (m.price - m.price * discount/100) AS discount_price
FROM person_discounts pd 
JOIN person p ON p.id = pd.person_id 
JOIN menu m ON m.pizzeria_id = pd.pizzeria_id 
ORDER BY person_name, pizza_name;
