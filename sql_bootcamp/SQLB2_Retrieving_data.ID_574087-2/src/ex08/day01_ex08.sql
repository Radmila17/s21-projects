SELECT order_date, 
	concat(p.name, ' (age:', p.age , ')') AS person_informmation
FROM person_order po 
NATURAL JOIN 
	(SELECT id AS person_id, name, age FROM person p ) AS p
ORDER BY order_date, person_informmation ASC;