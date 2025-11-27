SELECT p."name"
FROM person p
WHERE p.id IN 
	(SELECT person_id
	FROM person_order)
ORDER BY name;