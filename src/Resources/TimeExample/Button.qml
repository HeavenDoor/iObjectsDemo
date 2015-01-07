import QtQuick 2.4

Item {
	function setSource(url){
		image.source = url
	}
	id: topButton
	property int imgWidth: 0
	property int imgHeight: 0
	property string pressImg: ""
	property string normalImg: ""
	property string sourceImg: ""
	signal buttonClicked
	Image {
		id: image
		width: imgWidth
		height: imgHeight
		source: sourceImg

		MouseArea { 
			anchors.fill: parent
			hoverEnabled : true
			onPressed: image.source = pressImg
			onClicked: topButton.buttonClicked()
		}
	}
}	