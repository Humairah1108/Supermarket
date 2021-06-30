# Supermarket
Assignment in lieu of exams 2020
```
//--------------------------------------
A system needs to be developed to computerise a small supermarket. The system has two users, a cashier and a stock operator.
The Cashier subsystem should provide the following options: 

1. Query for an item price based on item’s barcode number. 
2. Record purchases by a customer.

Each time a customer arrives at the cashier, the latter simply inputs the barcode (3 digit) of all the items purchased by the customer and the system should lookup the ‘stock.txt’ file for the item's price and calculate the total for each customer. After scanning all the items, the cashier should be presented with a list of all items purchased, their price and the total (i.e in the same format as a receipt you would expect to see in a supermarket – Note in case there are several items of the same type these should appear only once on the receipt with the corresponding quantities and not multiple times). 
The cashier should then have options whether to edit the purchase list (i.e remove an item or edit it’s quantity) or to confirm the purchase. After the customer pays for his purchase, the transaction details (items, quantities and price) should be recorded in a timestamped file having as format dd_mm_yy_hh_mm_sec.txt where dd, mm,yy, hh, mm and sec represent the day, month, year, hour, minute, and second the purchase was confirmed. The system should also ensure that the ‘stock.txt’ file is updated accordingly. 

The stock operator simply receives all the deliveries for the shop and inputs a 3-digit barcode for each item, the name, the number of each item received, and each item’s selling price. After completing the data input, the stock file needs to be updated accordingly. 
The format of each receipt and timestamped file should be as follows : 

Item name	 ItemQty	 	ItemPrice	VatExcl 		ItemPriceVatIncl .

.
.
.
.

Total Excluding VAT: 
Total VAT: 
Total Incl. VAT 
Date of purchase 
Time Of Purchase 

The format of the tab-separated ‘stock.txt’ text file should be as follows: 
BarCode ItemName QtyInStock ReOrderLevel BuyingPrice SellingPrice %Vat 

Note: The system should validate all data input by the cashier and stock operator.
```
