-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE year = 2023 AND month = 7  AND day = 28 AND street = 'Humphrey Street';
SELECT activity, license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute = 16;
SELECT name,phone_number, passport_number FROM people WHERE license_plate = '5P2BI95';
SELECT  caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 29 AND receiver  = '(725) 555-4692';
SELECT name, passport_number, license_plate  FROM people WHERE phone_number ='(911) 555-0229';
SELECT name, passport_number, license_plate  FROM people WHERE phone_number ='(035) 555-2997';
SELECT seat FROM passengers WHERE passport_number = 7378796210;
 SELECT transcript from interviews WHERE day = 27 AND month = 7 AND year = 2023;
 SELECT transcript from interviews WHERE transcript = '%thief%';
SELECT license_plate, minute FROM bakery_security_logs WHERE year = 2023 AND day = 28 AND month = 7 AND hour = 10 AND activity = 'exit';
SELECT account_number, amount FROM  atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';
SELECT name FROM people WHERE id = (SELECT person_id FROM bank_accounts WHERE account_number = 49610011);
SELECT name FROM people WHERE license_plate = '94KL13X';
SELECT destination_airport_id, hour, minute FROM flights WHERE year = 2023 AND month = 7 AND day = 29 ORDER BY hour ASC, minute ASC LIMIT 1;
SELECT flight_id  FROM passengers WHERE passport_number = '5773159633 ';
SELECT phone_number FROM people WHERE passport_number = 5773159633;
SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND duration < 60;
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
