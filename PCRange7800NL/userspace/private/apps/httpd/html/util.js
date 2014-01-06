function isHexaDigit(digit) {
   var hexVals = new Array("0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                           "A", "B", "C", "D", "E", "F", "a", "b", "c", "d", "e", "f");
   var len = hexVals.length;
   var i = 0;
   var ret = false;

   for ( i = 0; i < len; i++ )
      if ( digit == hexVals[i] ) break;

   if ( i < len )
      ret = true;

   return ret;
}

function isValidKey(val, size) {
   var ret = false;
   var len = val.length;
   var dbSize = size * 2;

   if ( len == size )
      ret = true;
   else if ( len == dbSize ) {
      for ( var i = 0; i < dbSize; i++ )
         if ( isHexaDigit(val.charAt(i)) == false )
            break;
      if ( i == dbSize )
         ret = true;
   } else
      ret = false;

   return ret;
}


function isValidHexKey(val, size) {
   var ret = false;
   if (val.length == size) {
      for ( var i = 0; i < val.length; i++ ) {
         if ( isHexaDigit(val.charAt(i)) == false ) {
            break;
         }
      }
      if ( i == val.length ) {
         ret = true;
      }
   }

   return ret;
}


function isNameUnsafe(compareChar) {
   var unsafeString = "\"<>%\\^[]`\+\$\,='#&@.: \t";
	
   if ( unsafeString.indexOf(compareChar) == -1 && compareChar.charCodeAt(0) > 32
        && compareChar.charCodeAt(0) < 123 )
      return false; // found no unsafe chars, return false
   else
      return true;
}   

// Check if a name valid
function isValidName(name) {
   var i = 0;	
   
   for ( i = 0; i < name.length; i++ ) {
      if ( isNameUnsafe(name.charAt(i)) == true )
         return false;
   }

   return true;
}

// same as is isNameUnsafe but allow spaces
function isCharUnsafe(compareChar) {
   var unsafeString = "\"<>%\\^[]`\+\$\,='#&@.:\t";
	
   if ( unsafeString.indexOf(compareChar) == -1 && compareChar.charCodeAt(0) >= 32
        && compareChar.charCodeAt(0) < 123 )
      return false; // found no unsafe chars, return false
   else
      return true;
}   

function isValidNameWSpace(name) {
   var i = 0;	
   
   for ( i = 0; i < name.length; i++ ) {
      if ( isCharUnsafe(name.charAt(i)) == true )
         return false;
   }

   return true;
}

function isSameSubNet(lan1Ip, lan1Mask, lan2Ip, lan2Mask) {

   var count = 0;
   
   lan1a = lan1Ip.split('.');
   lan1m = lan1Mask.split('.');
   lan2a = lan2Ip.split('.');
   lan2m = lan2Mask.split('.');

   for (var i = 0; i < 4; i++) {
      l1a_n = parseInt(lan1a[i]);
      l1m_n = parseInt(lan1m[i]);
      l2a_n = parseInt(lan2a[i]);
      l2m_n = parseInt(lan2m[i]);
      if ((l1a_n & l1m_n) == (l2a_n & l2m_n))
         count++;
   }
   if (count == 4)
      return true;
   else
      return false;
}

function validIp(str, idx)
{
	var ch = /^[0-9]+$/;
	if ( str == null || str.length == 0)
		return false;
	if(str.indexOf('0')==0 && (idx==0 || str.length!=1 || idx==3))
		return false;
	return ch.test(str);
}
/*for check host IP*/
function isValidHostIp(address) {
	var ipParts = address.split('/');
	if (ipParts.length > 2) return false;
	if (ipParts.length == 2) {
		num = parseInt(ipParts[1]);
		if (num <= 0 || num > 32)
			return false;
	}

	if (ipParts[0] == '0.0.0.0' || ipParts[0] == '255.255.255.255' )
		return false;

	var addrParts = ipParts[0].split('.');
	if ( addrParts.length != 4 ) return false;
	for (var i = 0; i < 4; i++) {
		if (isNaN(addrParts[i]) || addrParts[i] ==""|| !validIp(addrParts[i], i))
			return false;
		num = parseInt(addrParts[i]);
		if ( num < 0 || num > 255 )
			return false;
/*Tammy added@20100413*/
		if(i==3 && ( num == 0 || num == 255 ))
		return false;
/*end of Tammy added*/    
	}
	return true;
}
function validRouteIp(str, idx)
{
	var ch = /^[0-9]+$/;
	if ((str == null) || (str.length == 0))
		return false;
	if(str.indexOf('0')==0 && (idx==0 || str.length!=1))
		return false;
	return ch.test(str);
}
function isValidRouteIp(address) {
	addrParts = address.split('.');
	if ( addrParts.length != 4 ) return false;
	for (var i = 0; i < 4; i++) {
		if (isNaN(addrParts[i]) || addrParts[i] ==""|| !validRouteIp(addrParts[i], i) )
			return false;
		num = parseInt(addrParts[i]);
		if ( num < 0 || num > 255 )
			return false;
	}
	return true;
}
function isValidIpAddress(address) {

   ipParts = address.split('/');
   if (ipParts.length > 2) return false;
   if (ipParts.length == 2) {
      num = parseInt(ipParts[1]);
      if (num <= 0 || num > 32)
         return false;
   }

   if (ipParts[0] == '0.0.0.0' ||
       ipParts[0] == '255.255.255.255' )
      return false;

   addrParts = ipParts[0].split('.');
   if ( addrParts.length != 4 ) return false;
   for (var i = 0; i < 4; i++) {
      if (isNaN(addrParts[i]) || addrParts[i] =="")
         return false;
      num = parseInt(addrParts[i]);
      if ( num < 0 || num > 255 )
         return false;
   }
   return true;
}
function isValidIpAddress6(address) {

   ipParts = address.split('/');
   if (ipParts.length > 2) return false;
   if (ipParts.length == 2) {
      if (isNumberStr(ipParts[1]) == false) return false;
      num = parseInt(ipParts[1]);
      if (num <= 0 || num > 128)
         return false;
   }

   var v = ipParts[0].split("::");
   if (v.length > 2) return false;
   addrParts = ipParts[0].split(':');
   if (addrParts.length < 3 || addrParts.length > 8)
      return false;
   for (var i = 0; i < addrParts.length; i++) {
      if ( addrParts[i] != "" ) {
         if (isValidHexKey (addrParts[i], addrParts[i].length)==false) return false; // sarah add
         num = parseInt(addrParts[i], 16);
      }
      if ( i == 0 ) {
//         if ( (num & 0xf000) == 0xf000 )
//            return false;	//can not be link-local, site-local or multicast address
         if (num == 0) return false; // sarah add, 20100416
      }
      else if ( (i + 1) == addrParts.length) {
         if ( num == 0 || num == 1)
            return false;	//can not be unspecified or loopback address
      }
      /* sarah remove, 20100416
      if ( num != 0 )
         break;
      */
   }
   return true;
}

function isValidPrefixLength(prefixLen) {
   var num;

   num = parseInt(prefixLen);
   if (num <= 0 || num > 128)
      return false;
   return true;
}

function areSamePrefix(addr1, addr2) {
   var i, j;
   var a = [0, 0, 0, 0, 0, 0, 0, 0];
   var b = [0, 0, 0, 0, 0, 0, 0, 0];

   addr1Parts = addr1.split(':');
   if (addr1Parts.length < 3 || addr1Parts.length > 8)
      return false;
   addr2Parts = addr2.split(':');
   if (addr2Parts.length < 3 || addr2Parts.length > 8)
      return false;
   j = 0;
   for (i = 0; i < addr1Parts.length; i++) {
      if ( addr1Parts[i] == "" ) {
		 if ((i != 0) && (i+1 != addr1Parts.length)) {
			j = j + (8 - addr1Parts.length + 1);
		 }
		 else {
		    j++;
		 }
	  }
	  else {
         a[j] = parseInt(addr1Parts[i], 16);
		 j++;
	  }
   }
   j = 0;
   for (i = 0; i < addr2Parts.length; i++) {
      if ( addr2Parts[i] == "" ) {
		 if ((i != 0) && (i+1 != addr2Parts.length)) {
			j = j + (8 - addr2Parts.length + 1);
		 }
		 else {
		    j++;
		 }
	  }
	  else {
         b[j] = parseInt(addr2Parts[i], 16);
		 j++;
	  }
   }
   //only compare 64 bit prefix
   for (i = 0; i < 4; i++) {
      if (a[i] != b[i]) {
	     return false;
	  }
   }
   return true;
}

function getLeftMostZeroBitPos(num) {
   var i = 0;
   var numArr = [128, 64, 32, 16, 8, 4, 2, 1];

   for ( i = 0; i < numArr.length; i++ )
      if ( (num & numArr[i]) == 0 )
         return i;

   return numArr.length;
}

function getRightMostOneBitPos(num) {
   var i = 0;
   var numArr = [1, 2, 4, 8, 16, 32, 64, 128];

   for ( i = 0; i < numArr.length; i++ )
      if ( ((num & numArr[i]) >> i) == 1 )
         return (numArr.length - i - 1);

   return -1;
}

function isValidSubnetMask(mask) {
   var i = 0, num = 0;
   var zeroBitPos = 0, oneBitPos = 0;
   var zeroBitExisted = false;

   if ( mask == '0.0.0.0' )
      return false;

   maskParts = mask.split('.');
   if ( maskParts.length != 4 ) return false;

   for (i = 0; i < 4; i++) {
      if ( isNaN(maskParts[i]) == true )
         return false;
      num = parseInt(maskParts[i]);
      if ( num < 0 || num > 255 )
         return false;
      if ( zeroBitExisted == true && num != 0 )
         return false;
      zeroBitPos = getLeftMostZeroBitPos(num);
      oneBitPos = getRightMostOneBitPos(num);
      if ( zeroBitPos < oneBitPos )
         return false;
      if ( zeroBitPos < 8 )
         zeroBitExisted = true;
   }

   return true;
}

function isValidPort(port) {
   var fromport = 0;
   var toport = 100;

   portrange = port.split(':');
   if ( portrange.length < 1 || portrange.length > 2 ) {
       return false;
   }
   if ( isNaN(portrange[0]) )
       return false;
   fromport = parseInt(portrange[0]);
   
   if ( portrange.length > 1 ) {
       if ( isNaN(portrange[1]) )
          return false;
       toport = parseInt(portrange[1]);
       if ( toport <= fromport )
           return false;      
   }
   
   if ( fromport < 1 || fromport > 65535 || toport < 1 || toport > 65535 )
       return false;
   
   return true;
}

function isValidNatPort(port) {
   var fromport = 0;
   var toport = 100;

   portrange = port.split('-');
   if ( portrange.length < 1 || portrange.length > 2 ) {
       return false;
   }
   if ( isNaN(portrange[0]) )
       return false;
   fromport = parseInt(portrange[0]);

   if ( portrange.length > 1 ) {
       if ( isNaN(portrange[1]) )
          return false;
       toport = parseInt(portrange[1]);
       if ( toport <= fromport )
           return false;
   }

   if ( fromport < 1 || fromport > 65535 || toport < 1 || toport > 65535 )
       return false;

   return true;
}

function isValidMacAddress(address) {
   var c = '';
   var num = 0;
   var i = 0, j = 0;
   var zeros = 0;

   addrParts = address.split(':');
   if ( addrParts.length != 6 ) return false;

   for (i = 0; i < 6; i++) {
      if ( addrParts[i] == '' )
         return false;
      for ( j = 0; j < addrParts[i].length; j++ ) {
         c = addrParts[i].toLowerCase().charAt(j);
         if ( (c >= '0' && c <= '9') ||
              (c >= 'a' && c <= 'f') )
            continue;
         else
            return false;
      }

      num = parseInt(addrParts[i], 16);
      if ( num == NaN || num < 0 || num > 255 )
         return false;
      if ( num == 0 )
         zeros++;
   }
   if (zeros == 6)
      return false;

   return true;
}

function isValidMacMask(mask) {
   var c = '';
   var num = 0;
   var i = 0, j = 0;
   var zeros = 0;
   var zeroBitPos = 0, oneBitPos = 0;
   var zeroBitExisted = false;

   maskParts = mask.split(':');
   if ( maskParts.length != 6 ) return false;

   for (i = 0; i < 6; i++) {
      if ( maskParts[i] == '' )
         return false;
      for ( j = 0; j < maskParts[i].length; j++ ) {
         c = maskParts[i].toLowerCase().charAt(j);
         if ( (c >= '0' && c <= '9') ||
              (c >= 'a' && c <= 'f') )
            continue;
         else
            return false;
      }

      num = parseInt(maskParts[i], 16);
      if ( num == NaN || num < 0 || num > 255 )
         return false;
      if ( zeroBitExisted == true && num != 0 )
         return false;
      if ( num == 0 )
         zeros++;
      zeroBitPos = getLeftMostZeroBitPos(num);
      oneBitPos = getRightMostOneBitPos(num);
      if ( zeroBitPos < oneBitPos )
         return false;
      if ( zeroBitPos < 8 )
         zeroBitExisted = true;
   }
   if (zeros == 6)
      return false;

   return true;
}

var hexVals = new Array("0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
              "A", "B", "C", "D", "E", "F");
var unsafeString = "\"<>%\\^[]`\+\$\,'#&";
// deleted these chars from the include list ";", "/", "?", ":", "@", "=", "&" and #
// so that we could analyze actual URLs

function isUnsafe(compareChar)
// this function checks to see if a char is URL unsafe.
// Returns bool result. True = unsafe, False = safe
{
   if ( unsafeString.indexOf(compareChar) == -1 && compareChar.charCodeAt(0) > 32
        && compareChar.charCodeAt(0) < 123 )
      return false; // found no unsafe chars, return false
   else
      return true;
}

function decToHex(num, radix)
// part of the hex-ifying functionality
{
   var hexString = "";
   while ( num >= radix ) {
      temp = num % radix;
      num = Math.floor(num / radix);
      hexString += hexVals[temp];
   }
   hexString += hexVals[num];
   return reversal(hexString);
}

function reversal(s)
// part of the hex-ifying functionality
{
   var len = s.length;
   var trans = "";
   for (var i = 0; i < len; i++)
      trans = trans + s.substring(len-i-1, len-i);
   s = trans;
   return s;
}

function convert(val)
// this converts a given char to url hex form
{
   return  "%" + decToHex(val.charCodeAt(0), 16);
}


function encodeUrl(val)
{
   var len     = val.length;
   var i       = 0;
   var newStr  = "";
   var original = val;

   for ( i = 0; i < len; i++ ) {
      if ( val.substring(i,i+1).charCodeAt(0) < 255 ) {
         // hack to eliminate the rest of unicode from this
         if (isUnsafe(val.substring(i,i+1)) == false)
            newStr = newStr + val.substring(i,i+1);
         else
            newStr = newStr + convert(val.substring(i,i+1));
      } else {
         // woopsie! restore.
         alert ("Found a non-ISO-8859-1 character at position: " + (i+1) + ",\nPlease eliminate before continuing.");
         newStr = original;
         // short-circuit the loop and exit
         i = len;
      }
   }

   return newStr;
}

var markStrChars = "\"'";

// Checks to see if a char is used to mark begining and ending of string.
// Returns bool result. True = special, False = not special
function isMarkStrChar(compareChar)
{
   if ( markStrChars.indexOf(compareChar) == -1 )
      return false; // found no marked string chars, return false
   else
      return true;
}

// use backslash in front one of the escape codes to process
// marked string characters.
// Returns new process string
function processMarkStrChars(str) {
   var i = 0;
   var retStr = '';

   for ( i = 0; i < str.length; i++ ) {
      if ( isMarkStrChar(str.charAt(i)) == true )
         retStr += '\\';
      retStr += str.charAt(i);
   }

   return retStr;
}

// Web page manipulation functions

function showhide(element, sh)
{
    var status;
    if (sh == 1) {
        //status = "block";
        status = "";
    }
    else {
        status = "none"
    }
    
	if (document.getElementById)
	{
		// standard
		document.getElementById(element).style.display = status;
	}
	else if (document.all)
	{
		// old IE
		document.all[element].style.display = status;
	}
	else if (document.layers)
	{
		// Netscape 4
		document.layers[element].display = status;
	}
}

// Load / submit functions

function getSelect(item)
{
	var idx;
	if (item.options.length > 0) {
	    idx = item.selectedIndex;
	    return item.options[idx].value;
	}
	else {
		return '';
    }
}

function setSelect(item, value)
{
	for (var i=0; i<item.options.length; i++) {
        if (item.options[i].value == value) {
        	item.selectedIndex = i;
        	break;
        }
    }
}

function setCheck(item, value)
{
    if ( value == '1' ) {
         item.checked = true;
    } else {
         item.checked = false;
    }
}

function setDisable(item, value)
{
    if ( value == 1 || value == '1' ) {
         item.disabled = true;
    } else {
         item.disabled = false;
    }     
}

function submitText(item)
{
	return '&' + item.name + '=' + item.value;
}

function submitSelect(item)
{
	return '&' + item.name + '=' + getSelect(item);
}


function submitCheck(item)
{
	var val;
	if (item.checked == true) {
		val = 1;
	} 
	else {
		val = 0;
	}
	return '&' + item.name + '=' + val;
}

/*New add js, Tammy*/
function isSafeStr(str)
{
	//var unsafeString = "\"%\\`\+#&| \t";
	var unsafeString = "\"|\\\t";

	for (var i = 0; i < unsafeString.length; i++ ) {
		if (str.indexOf(unsafeString.charAt(i)) > -1) return false;
	}
	return true;
}

function chgMACFormat(mac)
{
		var a=mac.split(":");
		if (a.length > 1) return mac;
		var b=mac.split("-");
		if (b.length < 2) return mac;
		var str=b.join(":");
		return str;
}
function showElm(elm, t)
{
	var idd=document.getElementById(elm);
	var fg=(t==1)?"":"none";
	idd.style.display=fg;
}
function showEntries(elm, t)
{
	var idd;
	var fg=(t==1)?"":"none";
	for(var i=0; i<elm.length; i++)
	{
		idd=document.getElementById(elm[i]);
		idd.style.display=fg;
	}
}
function showEntriesDisable(elm, t)
{
	var idd;
	var fg=(t==1)?true:false;
	for(var i=0; i<elm.length; i++)
	{
		document.getElementById(elm[i]).disabled=fg;
	}
}
// Sarah add -------------------------------------------------------------
function isCommonIp4(address) {

   addrParts = address.split('.');
   if (addrParts.length != 4) return false;
   if (address == "0.0.0.0" || address == "255.255.255.255") return false;
   for (var i = 0; i < 4; i++) {
      if (isNaN(addrParts[i]) || addrParts[i] =="")
         return false;
      num = parseInt(addrParts[i]);
      if ( num < 0 || num > 255 )
         return false;
   }
   return true;
}

function isCommonIp6(address) {
   var n_zero=0;
   if (address == "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff") return false;
   var v = address.split("::");
   if (v.length > 2) return false;
   addrParts = address.split(':');
   if (addrParts.length < 3 || addrParts.length > 8)
      return false;
   for (var i = 0; i < addrParts.length; i++) {
      if (addrParts[i] == "") continue;
      if (!isValidHexKey (addrParts[i], addrParts[i].length)) return false; // sarah add
      if (parseInt(addrParts[i], 16) != 0) n_zero++;
   }
   return (n_zero ? true : false);
}

function Ipv6toNum (ips, val)
{
	var i, idx=0;
	if (isCommonIp6 (ips) == false) return false;
	var v=ips.split ("::");
	if (v.length > 2) return false;
	var s1, s2;
	s1=v[0].split(":");
	if (v.length > 1) s2 = v[1].split(":");
	for (i = 0; i < s1.length; i++) {
		if (!isValidHexKey (s1[i], s1[i].length)) return false;
		val[idx++] = parseInt (s1[i], 16);
	}
	if (v.length > 1) {
		var zeros = 8 - s1.length - s2.length;
		for (i = 0; i < zeros; i++) val[idx++] = 0;
		for (i = 0; i < s2.length; i++) {
			if (!isValidHexKey (s2[i], s2[i].length)) return false;
			val[idx++] = parseInt (s2[i], 16);
		}
	}
	return true;
}
function cmpIpv6 (ip1, ip2)
{
	var val1=new Array(8), val2=new Array(8);
	if (Ipv6toNum (ip1, val1) == false) return -1;
	if (Ipv6toNum (ip2, val2) == false) return -1;
	var ss=0;
	for (var i = 0; i < 8; i++) {
		if (val1[i] > val2[i] && ss == 0) return 1;
		else if (val1[i] < val2[i]) ss++;
	}
	return 0;
}

function Ipv4toNum (ips, val)
{
	if (isCommonIp4 (ips) == false) return false;
	var s = ips.split (".");
	if (s.length != 4) return false;
	for (var i = 0; i < 4; i++) {
		if (isNaN (s[i])) return false;
		val[i] = parseInt (s[i]);
	}
	return true;
}

function cmpIpv4 (ip1, ip2)
{
	var val1=new Array(4), val2=new Array (4);
	if (Ipv4toNum (ip1, val1) == false) return -1;
	if (Ipv4toNum (ip2, val2) == false) return -1;
	var ss = 0;
	for (var i = 0; i < 4; i++) {
		if (val1[i] > val2[i] && ss == 0) return 1;
		else if (val1[i] < val2[i]) ss++;
	}
	return 0;
}
function isValidNameL1(str)
{
	var unsafeString = "\"|\\\t";

	for (var i = 0; i < unsafeString.length; i++ ) {
		if (str.indexOf(unsafeString.charAt(i)) > -1) return false;
	}
	return true;
}
function isDigit(digit) {
   var Vals = new Array("0", "1", "2", "3", "4", "5", "6", "7", "8", "9");
   var len = Vals.length;
   var i = 0;
   var ret = false;

   for ( i = 0; i < len; i++ )
      if ( digit == Vals[i] ) break;

   if ( i < len )
      ret = true;

   return ret;
}
function isNumberStr(str)
{
	if (str == "") return false;
	for (var i = 0; i < str.length; i++) {
		if (isDigit(str.charAt(i)) == false) return false;
	}
	return true;
}
// sarah end ------------------------------------------------------------
