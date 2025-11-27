insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');


WITH currency_dates AS (
    SELECT 
        b.user_id,
        b.money,
        b.updated AS balance_updated,
        b.currency_id,
        c.name AS currency_name,
        c.rate_to_usd,
        c.updated AS currency_updated,
        MAX(CASE WHEN c.updated <= b.updated THEN c.updated END)  -- в прошлом 
            OVER (PARTITION BY b.user_id, b.currency_id, b.updated) AS t1,
        MIN(CASE WHEN c.updated > b.updated THEN c.updated END)
            OVER (PARTITION BY b.user_id, b.currency_id, b.updated) AS t2
    FROM balance b
    JOIN currency c ON b.currency_id = c.id), 
	before_currency AS (
		SELECT 
        cd.user_id,
        cd.money,
        cd.balance_updated,
        cd.currency_id,
        cd.currency_name,
        cd.t1,
        c.rate_to_usd AS rate
		FROM currency_dates cd
		JOIN currency c ON c.id = cd.currency_id AND c.updated = cd.t1),
	after_currency AS (
		SELECT 
        cd.user_id,
        cd.money,
        cd.balance_updated,
        cd.currency_id,
        cd.currency_name,
        cd.t2,
        c.rate_to_usd AS rate
		FROM currency_dates cd
		JOIN currency c ON c.id = cd.currency_id AND c.updated = cd.t2
		WHERE cd.t1 IS NULL),
	 combine_currency as(
	 SELECT * FROM before_currency
	 UNION
	 SELECT * FROM after_currency)
SELECT 
    COALESCE(u.name, 'not defined') AS name,
    COALESCE(u.lastname, 'not defined') AS lastname,
    cc.currency_name,
    (cc.money * cc.rate) AS currency_in_usd
FROM combine_currency cc
LEFT JOIN "user" u ON u.id = cc.user_id
ORDER BY name DESC, lastname, cc.currency_name;
	
