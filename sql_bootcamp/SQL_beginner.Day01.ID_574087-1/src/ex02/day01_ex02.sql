SELECT pizza_name
FROM menu m1
WHERE NOT EXISTS (
	SELECT 1
	FROM menu m2 
	WHERE m1.pizza_name = m2.pizza_name AND m1.id > m2.id	
)
ORDER BY pizza_name DESC;