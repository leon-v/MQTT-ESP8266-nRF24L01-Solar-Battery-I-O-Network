function cleanSSI(elementId){
	var element = document.getElementById(elementId);
	element.value = element.value.replace(/<!--(.*?)-->/gm, "");
}