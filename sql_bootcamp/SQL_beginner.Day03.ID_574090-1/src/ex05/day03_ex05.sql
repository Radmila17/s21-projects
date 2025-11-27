WITH an_visits AS 
		(SELECT piz.id, piz.name 
		FROM person_visits pv 
		JOIN pizzeria piz ON pv.pizzeria_id = piz.id 
		JOIN person p ON p.id = pv.person_id 
		WHERE p."name" = 'Andrey'),
	an_orders AS 
		(SELECT DISTINCT  piz.id, piz.name 
		FROM person_order po
		JOIN person p ON po.person_id  = p.id AND p.name = 'Andrey'
		JOIN menu m ON m.id = po.menu_id 
		JOIN pizzeria piz ON m.pizzeria_id = piz.id 
		),
	without_order AS 
		(SELECT av.id
		FROM an_visits av
		EXCEPT 
		SELECT ao.id
		FROM an_orders ao)
SELECT piz.name AS pizzeria_name
FROM without_order wo
JOIN pizzeria piz ON piz.id = wo.id 
ORDER BY pizzeria_name;


SELECT DISTINCT piz.name AS pizzeria_name
FROM person_visits pv
JOIN pizzeria piz ON pv.pizzeria_id = piz.id
JOIN person p ON p.id = pv.person_id
WHERE p.name = 'Andrey'
AND NOT EXISTS (
    SELECT *
    FROM person_order po
    JOIN menu m ON po.menu_id = m.id
    WHERE po.person_id = p.id
      AND m.pizzeria_id = piz.id
);
