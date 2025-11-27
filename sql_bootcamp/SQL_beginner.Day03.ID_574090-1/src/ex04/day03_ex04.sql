WITH females_orders AS
		(SELECT piz.id, piz.name
		FROM person_order po
		JOIN menu m ON po.menu_id = m.id
		JOIN pizzeria piz ON piz.id = m.pizzeria_id 
		JOIN person p ON p.id = po.person_id AND p.gender = 'female'
		GROUP BY piz.id, piz.name),
	males_orders AS 
		(SELECT piz.id, piz.name
		FROM person_order po
		JOIN menu m ON po.menu_id = m.id
		JOIN pizzeria piz ON piz.id = m.pizzeria_id 
		JOIN person p ON p.id = po.person_id AND p.gender = 'male'
		GROUP BY piz.id, piz.name)
-- You can use EXCEPT. And it will be more understandable 
SELECT fo.name AS pizzeria_name
FROM females_orders fo
EXCEPT
SELECT mo.name
FROM males_orders mo
UNION
-- Or you can use LEFT JOIN with WHERE command. But it will be a little more difficult
SELECT mo.name AS pizzeria_name
FROM males_orders mo
LEFT JOIN females_orders fo ON mo.id = fo.id
WHERE fo.id IS NULL
ORDER BY pizzeria_name;

