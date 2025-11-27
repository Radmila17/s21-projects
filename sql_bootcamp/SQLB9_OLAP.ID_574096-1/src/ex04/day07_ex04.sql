SELECT p.name, count(*) AS count_of_visits
FROM person_visits pv 
JOIN person p ON p.id = pv.person_id 
GROUP BY p.name
HAVING count(*)> 3;