WITH visits AS 
	(SELECT person_id, count(*) AS count_of_visits
	FROM person_visits pv 
	GROUP BY person_id
	ORDER BY count_of_visits DESC, person_id)
SELECT p.name, v.count_of_visits
FROM person p 
JOIN visits v ON p.id = v.person_id
ORDER BY count_of_visits DESC, p."name" 
LIMIT 4;
