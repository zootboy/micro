var NAVTREE =
[
  [ "LUFA Library - uIP Powered Webserver Project", "index.html", [
    [ "uIP Powered Webserver Project", "index.html", null ],
    [ "Data Structures", "annotated.html", [
      [ "DHCP_Header_t", "a00001.html", null ],
      [ "MIME_Type_t", "a00002.html", null ],
      [ "USB_Descriptor_Configuration_t", "a00003.html", null ]
    ] ],
    [ "Data Structure Index", "classes.html", null ],
    [ "Data Fields", "functions.html", null ],
    [ "File List", "files.html", [
      [ "Descriptors.c", "a00004.html", null ],
      [ "Descriptors.h", "a00005.html", null ],
      [ "USBDeviceMode.c", "a00022.html", null ],
      [ "USBDeviceMode.h", "a00023.html", null ],
      [ "USBHostMode.c", "a00024.html", null ],
      [ "USBHostMode.h", "a00025.html", null ],
      [ "Webserver.c", "a00026.html", null ],
      [ "Webserver.h", "a00027.html", null ],
      [ "Lib/DataflashManager.c", "a00006.html", null ],
      [ "Lib/DataflashManager.h", "a00007.html", null ],
      [ "Lib/DHCPClientApp.c", "a00008.html", null ],
      [ "Lib/DHCPClientApp.h", "a00009.html", null ],
      [ "Lib/DHCPCommon.c", "a00010.html", null ],
      [ "Lib/DHCPCommon.h", "a00011.html", null ],
      [ "Lib/DHCPServerApp.c", "a00012.html", null ],
      [ "Lib/DHCPServerApp.h", "a00013.html", null ],
      [ "Lib/HTTPServerApp.c", "a00014.html", null ],
      [ "Lib/HTTPServerApp.h", "a00015.html", null ],
      [ "Lib/SCSI.c", "a00016.html", null ],
      [ "Lib/SCSI.h", "a00017.html", null ],
      [ "Lib/TELNETServerApp.c", "a00018.html", null ],
      [ "Lib/TELNETServerApp.h", "a00019.html", null ],
      [ "Lib/uIPManagement.c", "a00020.html", null ],
      [ "Lib/uIPManagement.h", "a00021.html", null ]
    ] ],
    [ "Directories", "dirs.html", [
      [ "Lib", "dir_2c9e93bd891e52c526f7f58e0136d327.html", [
        [ "DataflashManager.c", "a00006.html", null ],
        [ "DataflashManager.h", "a00007.html", null ],
        [ "DHCPClientApp.c", "a00008.html", null ],
        [ "DHCPClientApp.h", "a00009.html", null ],
        [ "DHCPCommon.c", "a00010.html", null ],
        [ "DHCPCommon.h", "a00011.html", null ],
        [ "DHCPServerApp.c", "a00012.html", null ],
        [ "DHCPServerApp.h", "a00013.html", null ],
        [ "HTTPServerApp.c", "a00014.html", null ],
        [ "HTTPServerApp.h", "a00015.html", null ],
        [ "SCSI.c", "a00016.html", null ],
        [ "SCSI.h", "a00017.html", null ],
        [ "TELNETServerApp.c", "a00018.html", null ],
        [ "TELNETServerApp.h", "a00019.html", null ],
        [ "uIPManagement.c", "a00020.html", null ],
        [ "uIPManagement.h", "a00021.html", null ]
      ] ]
    ] ],
    [ "Globals", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

