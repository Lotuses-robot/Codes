function getElementByXpath(xpath){var element=document.evaluate(xpath,document).iterateNext();return element}const th=50;var RNA=new Array();function getRNAOnce(){try{getElementByXpath('//*[@id="evolution-rna"]/a[1]/span').click()}catch{}}function getRNA(){for(var i=1;i<=th;i++){RNA[i]=setInterval("getRNAOnce()",0)}}function stopGetRNA(){for(var i=1;i<=th;i++){clearInterval(RNA[i])}}var DNA=new Array();function getDNAOnce(){try{getElementByXpath('//*[@id="evolution-dna"]/a[1]/span').click()}catch{}}function getDNA(){for(var i=1;i<=th;i++){DNA[i]=setInterval("getDNAOnce()",0)}}function stopGetDNA(){for(var i=1;i<=th;i++){clearInterval(DNA[i])}}var food=new Array();function getFoodOnce(){try{getElementByXpath('//*[@id="city-food"]/a[1]/span').click()}catch{}}function getFood(){for(var i=1;i<=th;i++){food[i]=setInterval("getFoodOnce()",0)}}function stopGetFood(){for(var i=1;i<=th;i++){clearInterval(food[i])}}var wood=new Array();function getWoodOnce(){try{getElementByXpath('//*[@id="city-lumber"]/a[1]/span').click()}catch{}}function getWood(){for(var i=1;i<=th;i++){wood[i]=setInterval("getWoodOnce()",0)}}function stopGetWood(){for(var i=1;i<=th;i++){clearInterval(wood[i])}}var stone=new Array();function getStoneOnce(){try{getElementByXpath('//*[@id="city-stone"]/a[1]/span').click()}catch{}}function getStone(){for(var i=1;i<=th;i++){stone[i]=setInterval("getStoneOnce()",0)}}function stopGetStone(){for(var i=1;i<=th;i++){clearInterval(stone[i])}}insertlb=document.createElement("div")insertlb.id='btm'insertlb.setAttribute('style','position:relative;top:600px;left:20px')bodyttt=getElementByXpath('/html/body');bf=getElementByXpath('//*[@id="topBar"]')bodyttt.insertBefore(insertlb,bf)function insertButton(cont,oncl){var insertLabel=document.createElement("button");insertLabel.append(cont);insertLabel.setAttribute("onclick",oncl);insertLabel.setAttribute("style","width: 50px;")bodyb=getElementByXpath('//*[@id="btm"]');bodyb.appendChild(insertLabel)}insertButton('Start Wood','getWood()');insertButton('Stop Wood','stopGetWood()');insertButton('Start Food','getFood()');insertButton('Stop Food','stopGetFood()');insertButton('Start Stone','getStone()');insertButton('Stop Stone','stopGetStone()');