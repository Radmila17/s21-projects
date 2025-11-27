SELECT 
    address, 
    round((MAX(age) - (MIN(age)::float / MAX(age)))::numeric, 2) AS formula, 
    round (AVG(age),2) AS average,
    (CASE
        WHEN (MAX(age) - (MIN(age) / MAX(age))) > AVG(age) THEN true
        ELSE false
    END) AS comparison
FROM person 
GROUP BY address
ORDER BY address;