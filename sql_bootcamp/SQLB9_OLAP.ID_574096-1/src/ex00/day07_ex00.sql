SELECT person_id, count(*) AS count_of_visits
FROM person_visits pv 
GROUP BY person_id
ORDER BY count_of_visits DESC, person_id;