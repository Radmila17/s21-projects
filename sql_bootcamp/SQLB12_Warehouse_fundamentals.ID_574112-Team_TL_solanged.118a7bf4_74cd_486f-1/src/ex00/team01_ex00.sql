WITH last_currency_rates AS (
    SELECT DISTINCT ON (c.id)
           c.id,
           c.name, 
           c.rate_to_usd,
           c.updated
    FROM Currency c
    ORDER BY c.id, c.updated DESC)
SELECT COALESCE (u.name, 'not defined') AS "name",
		COALESCE (u.lastname, 'not defined') AS last_name,
		bal."type" AS "type",
		sum (bal.money) AS volume,
		COALESCE (l_cur."name", 'not defined') AS currency_name,
		COALESCE (l_cur.rate_to_usd, 1) AS last_rate_to_usd,
		COALESCE (l_cur.rate_to_usd, 1) * sum (bal.money) AS total_volume_in_usd
FROM balance bal
LEFT JOIN "user" u ON bal.user_id = u.id
LEFT JOIN last_currency_rates l_cur ON l_cur.id = bal.currency_id 
GROUP BY u.name, u.lastname,bal."type", currency_name, last_rate_to_usd
ORDER BY name DESC, last_name, "type";
		
	