SELECT p.name, sum(c) AS total_count 
FROM 
		((SELECT p.name, count(*) AS c, 'order' AS action_type
		FROM person_order po
		JOIN menu m ON m.id = po.menu_id
		JOIN pizzeria p ON p.id = m.pizzeria_id 
		GROUP BY p.name, p.id
		)
		UNION
		(SELECT p.name, count(*) AS c, 'visit' AS action_type
		FROM person_visits pv 
		JOIN pizzeria p ON p.id = pv.pizzeria_id 
		GROUP BY p.name, pv.pizzeria_id
		)) AS p
GROUP BY p.name
ORDER BY total_count DESC, p.name;