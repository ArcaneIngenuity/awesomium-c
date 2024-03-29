/**
 * @file WebView.h
 *
 * @author
 *
 * This file is a part of Awesomium, a library that makes it easy for 
 * developers to embed the web in their applications.
 *
 * Website: <http://www.khrona.com/products/awesomium>
 * 
 * Copyright (C) 2010 Khrona. All rights reserved. Awesomium is a 
 * trademark of Khrona.
 */

#ifndef __AWESOMIUM_WEB_VIEW_H__
#define __AWESOMIUM_WEB_VIEW_H__

#include "PlatformUtils.h"
#include "WebKeyboardEvent.h"
#include "WebViewListener.h"
#include "JSValue.h"
#include "RenderBuffer.h"
#include "ResourceInterceptor.h"
#include <string>

namespace Awesomium {
	
	/**
	 * Mouse button enumerations, used with WebView::injectMouseDown 
	 * and WebView::injectMouseUp
	 */
	enum MouseButton {
		LEFT_MOUSE_BTN,
		MIDDLE_MOUSE_BTN,
		RIGHT_MOUSE_BTN
	};
	
	/**
	 * URL Filtering mode enumerations, used by WebView::setURLFilteringMode
	 */
	enum URLFilteringMode {
		
		// No filtering
		UFM_NONE = 0,
		
		/**
		 * All resource requests and page navigations are ALLOWED 
		 * except those that match the URL filters specified.
		 */
		UFM_BLACKLIST, 
		
		/**
		 * All resource requests and page navigations are DENIED 
		 * except those that match the URL filters specified.
		 */
		UFM_WHITELIST
	};
	
	/**
	 * A map of string key/values representing an HTTP header.
	 */
	typedef std::map<std::string, std::string> HeaderDefinition;
	
	/**
	 * A WebView is similiar to a "tab" in a browser. You load pages into a 
	 * WebView, interact with it, and render it on-the-fly to a pixel buffer 
	 * (e.g., for use in an image/texture/etc). You create WebViews using the 
	 * WebCore (see WebCore::createWebView).
	 */
	class _OSMExport WebView
	{
	public:
		
		/**
		 * Queue this WebView for destruction by the WebCore.
		 */
		virtual void destroy() = 0;
		
		/**
		 * Register a WebViewListener to handle notifications of various events.
		 *
		 * @param	listener	The WebViewListener to register or NULL to clear 
		 *                      any current registrations.
		 */
		virtual void setListener(WebViewListener* listener) = 0;
		
		/**
		 * Retrieves the current WebViewListener.
		 *
		 * @return	If a WebViewListener is registered, returns a pointer to the 
		 *          instance, otherwise returns 0.
		 */
		virtual WebViewListener* getListener() = 0;
		
		/**
		 * Set a Resource Interceptor instance to intercept resource requests
		 * for this WebView.
		 *
		 * @param	interceptor	The ResourceInterceptor instance to register or
		 *						pass NULL to clear any current regisration.
		 */
		virtual void setResourceInterceptor(ResourceInterceptor* interceptor) = 0;
		
		/**
		 * Retrieves the current ResourceInterceptor.
		 *
		 * @return	If a ResourceInterceptor is registered, returns a pointer
		 *          to the instance, otherwise returns 0.
		 */
		virtual ResourceInterceptor* getResourceInterceptor() = 0;
		
		/**
		 * Loads a URL into the WebView asynchronously.
		 *
		 * @param	url	The URL to load.
		 *
		 * @param	frameName	Optional, the name of the frame to load the URL 
		 *                      in; leave this blank to load in the main frame.
		 *
		 * @param	username	Optional, if the URL requires authentication, 
		 *                      the username to authorize as.
		 *
		 * @param	password	Optional, if the URL requires authentication, 
		 *                      the password to use.
		 */
		virtual void loadURL(const std::string& url, 
							 const std::wstring& frameName = L"", 
							 const std::string& username = "", 
							 const std::string& password = "") = 0;
		
		/**
		 * Loads a URL into the WebView asynchronously.
		 *
		 * @param	url	The URL to load.
		 *
		 * @param	frameName	Optional, the name of the frame to load the URL 
		 *                      in; leave this blank to load in the main frame.
		 *
		 * @param	username	Optional, if the URL requires authentication, 
		 *                      the username to authorize as.
		 *
		 * @param	password	Optional, if the URL requires authentication, 
		 *					    the password to use.
		 */
		virtual void loadURL(const std::wstring& url, 
							 const std::wstring& frameName = L"", 
							 const std::string& username = "", 
							 const std::string& password = "") = 0;
		
		/**
		 * Loads a string of HTML into the WebView asynchronously.
		 *
		 * @param	html	The HTML string (ASCII) to load.
		 *
		 * @param	frameName	Optional, the name of the frame to load the HTML
		 *                      in; leave this blank to load in the main frame.
		 *
		 * @note	The base directory (specified via WebCore::setBaseDirectory) 
		 *          will be used to resolve relative URLs/resources (such as 
		 *          images, links, etc).
		 */
		virtual void loadHTML(const std::string& html, 
							  const std::wstring& frameName = L"") = 0;
		
		/**
		 * Loads a string of HTML into the WebView asynchronously.
		 *
		 * @param	html	The HTML string (wide) to load.
		 *
		 * @param	frameName	Optional, the name of the frame to load the HTML 
		 *                      in; leave this blank to load in the main frame.
		 *
		 * @note	The base directory (specified via WebCore::setBaseDirectory)
		 *          will be used to resolve relative URLs/resources (such as 
		 *          images, links, etc).
		 */
		virtual void loadHTML(const std::wstring& html, 
							  const std::wstring& frameName = L"") = 0;
		
		/**
		 * Loads a local file into the WebView asynchronously.
		 *
		 * @param	file	The file to load.
		 *
		 * @param	frameName	Optional, the name of the frame to load the file
		 *                      in; leave this blank to load in the main frame.
		 *
		 * @note	The file should exist within the base directory (specified 
		 *          via WebCore::setBaseDirectory).
		 */
		virtual void loadFile(const std::string& file, 
							  const std::wstring& frameName = L"") = 0;
		
		/**
		 * Navigates back/forward in history via a relative offset.
		 *
		 * @note
		 *	For example, to go back one page:
		 *		myView->goToHistoryOffset(-1);
		 *	Or, to go forward one page:
		 *		myView->goToHistoryOffset(1);
		 *
		 * @param	offset	The relative offset in history to navigate to.
		 */
		virtual void goToHistoryOffset(int offset) = 0;

		/**
		 * Stops the current navigation.
		 */
		virtual void stop() = 0;
		
		/**
		 * Reloads the current page.
		 */
		virtual void reload() = 0;
		
		/**
		 * Executes a string of Javascript in the context of the current page 
		 * asynchronously.
		 *
		 * @param	javascript	The ASCII string of Javascript to execute.
		 *
		 * @param	frameName	Optional, the name of the frame to execute in; 
		 *                      leave this blank to execute in the main frame.
		 */
		virtual void executeJavascript(const std::string& javascript, 
									   const std::wstring& frameName = L"") = 0;
		
		/**
		 * Executes a string of Javascript in the context of the current page 
		 * asynchronously.
		 *
		 * @param	javascript	The wide string of Javascript to execute.
		 *
		 * @param	frameName	Optional, the name of the frame to execute in; 
		 *                      leave this blank to execute in the main frame.
		 */
		virtual void executeJavascript(const std::wstring& javascript, 
									   const std::wstring& frameName = L"") = 0;
		
		/**
		 * Executes a string of Javascript in the context of the current page 
		 * asynchronously with a result.
		 *
		 * @param	javascript	The ASCII string of Javascript to execute.
		 *
		 * @param	frameName	Optional, the name of the frame to execute in; 
		 *                      leave this blank to execute in the main frame.
		 *
		 * @return	Returns a 'FutureJSValue' which is basically an 'IOU' for 
		 *          the future JSValue result. You can obtain the actual result
		 *          via FutureJSValue::get later.
		 */
		virtual Awesomium::FutureJSValue executeJavascriptWithResult(
									const std::string& javascript, 
									const std::wstring& frameName = L"") = 0;
		
		/**
		 * Executes a string of Javascript in the context of the current page 
		 * asynchronously with a result.
		 *
		 * @param	javascript	The wide string of Javascript to execute.
		 *
		 * @param	frameName	Optional, the name of the frame to execute in; 
		 *                      leave this blank to execute in the main frame.
		 *
		 * @return	Returns a 'FutureJSValue' which is basically an 'IOU' for 
		 *          the future JSValue result. You can obtain the actual result
		 *          via FutureJSValue::get later.
		 */
		virtual Awesomium::FutureJSValue executeJavascriptWithResult(
									const std::wstring& javascript, 
									const std::wstring& frameName = L"") = 0;
		
		/**
		 * Call a certain function defined in Javascript directly.
		 *
		 * @param	object	The name of the object that contains the function, 
		 *                  pass an empty string if the function is defined in 
		 *                  the global scope.
		 *
		 * @param	function	The name of the function.
		 *
		 * @param	args	The arguments to pass to the function.
		 *
		 * @param	frameName	Optional, the name of the frame to execute in; 
		 *                      leave this blank to execute in the main frame.
		 */
		virtual void callJavascriptFunction(const std::wstring& object, 
											const std::wstring& function, 
											const JSArguments& args, 
											const std::wstring& frameName = L"") = 0;
		
		/**
		 * Creates a new global Javascript object that will persist throughout 
		 * the lifetime of this WebView. This object is managed directly by 
		 * Awesomium and so you can modify its properties and bind callback 
		 * functions via WebView::setObjectProperty and 
		 * WebView::setObjectCallback, respectively.
		 *
		 * @param	objectName	The name of the object.
		 */
		virtual void createObject(const std::wstring& objectName) = 0;
		
		/**
		 * Destroys a Javascript object previously created by 
		 * WebView::createObject.
		 *
		 * @param	objectName	The name of the object to destroy.
		 */
		virtual void destroyObject(const std::wstring& objectName) = 0;
		
		/**
		 * Sets a property of a Javascript object previously created by 
		 * WebView::createObject.
		 *
		 * @param	objectName	The name of the Javascript object.
		 *
		 * @param	propName	The name of the property.
		 *
		 * @param	value	The javascript-value of the property.
		 */
		virtual void setObjectProperty(const std::wstring& objectName, 
									   const std::wstring& propName, 
									   const JSValue& value) = 0;
		
		/**
		 * Sets a callback function of a Javascript object previously created 
		 * by WebView::createObject. This is very useful for passing events 
		 * from Javascript to C++. To receive notification of the callback, a 
		 * WebViewListener should be registered (see WebView::setListener and 
		 * WebViewListener::onCallback).
		 *
		 * @param	objectName	The name of the Javascript object.
		 *
		 * @param	callbackName	The name of the callback function.
		 */
		virtual void setObjectCallback(const std::wstring& objectName, 
									   const std::wstring& callbackName) = 0;
		
		/**
		 * Returns whether or not a page is currently loading in the WebView.
		 *
		 * @return	If a page is loading, returns true, otherwise returns false.
		 */
		virtual bool isLoadingPage() = 0;
		
		/**
		 * Returns whether or not the WebView is dirty and needs to be 
		 * re-rendered via WebView::render.
		 *
		 * @return	If the WebView is dirty, returns true, otherwise returns 
		 *          false.
		 */
		virtual bool isDirty() = 0;
		
		/**
		 * Returns the bounds of the area that has changed since the last call 
		 * to WebView::render.
		 *
		 * @return	The bounds of the dirty area.
		 */
		virtual Rect getDirtyBounds() = 0;
		
		/**
		 * Renders this WebView into an offscreen render buffer and clears the 
		 * dirty state.
		 *
		 * @return	A pointer to the internal render buffer that was used to 
		 *           render this WebView. This value may change between renders 
		 *           and may return NULL if the WebView has crashed.
		 */
		virtual const RenderBuffer* render() = 0;

		/**
		 * All rendering is actually done asynchronously in a separate process
		 * and so the page is usually continuously rendering even if you never 
		 * call WebView::render. Call this to temporarily pause rendering.
		 */
		virtual void pauseRendering() = 0;

		/**
		 * Resume rendering after all call to WebView::pauseRendering.
		 */
		virtual void resumeRendering() = 0;

		/**
		 * Injects a mouse-move event in local coordinates.
		 *
		 * @param	x	The absolute x-coordinate of the mouse (localized to 
		 *              the WebView).
		 *
		 * @param	y	The absolute y-coordinate of the mouse (localized to 
		 *              the WebView).
		 */
		virtual void injectMouseMove(int x, int y) = 0;
		
		/**
		 * Injects a mouse-down event.
		 *
		 * @param	button	The button that was pressed.
		 */
		virtual void injectMouseDown(Awesomium::MouseButton button) = 0;
		
		/**
		 * Injects a mouse-up event.
		 *
		 * @param	button	The button that was released.
		 */
		virtual void injectMouseUp(Awesomium::MouseButton button) = 0;
		
		/**
		 * Injects a mouse-wheel event.
		 *
		 * @param	scrollAmount	The relative amount of pixels to scroll by.
		 */
		virtual void injectMouseWheel(int scrollAmount) = 0;
		
		/**
		 * Injects a keyboard event. See WebKeyboardEvent.h for more info.
		 *
		 * @param	keyboardEvent	The keyboard event to inject.
		 */
		virtual void injectKeyboardEvent(const WebKeyboardEvent& keyboardEvent) = 0;
		
		/**
		 * Invokes a 'cut' action using the system clipboard.
		 */
		virtual void cut() = 0;
		
		/**
		 * Invokes a 'copy' action using the system clipboard.
		 */
		virtual void copy() = 0;
		
		/**
		 * Invokes a 'paste' action using the system clipboard.
		 */
		virtual void paste() = 0;
		
		/**
		 * Selects all items on the current page.
		 */
		virtual void selectAll() = 0;
		
		/**
		 * Zooms the page a specified percent.
		 *
		 * @param	zoomPercent	The percent of the page to zoom to. Valid range
		 *                      is from 10% to 500%.
		 */
		virtual void setZoom(int zoomPercent) = 0;
		
		/**
		 * Resets the zoom level.
		 */
		virtual void resetZoom() = 0;
		
		/**
		 * Resizes this WebView to certain dimensions.
		 *
		 * @param	width	The width in pixels to resize to.
		 *
		 * @param	height	The height in pixels to resize to.
		 *
		 * @param	waitForRepaint	Whether or not to wait for the WebView
		 *                          to finish repainting.
		 *
		 * @param	repaintTimeoutMs	The maximum amount of time to wait
		 *                              for a repaint, in milliseconds.
		 *
		 * @return	Returns true if the resize was successful. This operation
		 *          can fail if there is another resize already pending (see
		 *          WebView::isResizing) or if the repaint timeout was exceeded.
		 */
		virtual bool resize(int width, 
							int height, 
							bool waitForRepaint = true, 
							int repaintTimeoutMs = 300) = 0;

		/**
		* Checks whether or not there is a resize operation pending.
		*
		* @return	Returns true if we are waiting for the WebView process to
		*           return acknowledgement of a pending resize operation.
		*/
		virtual bool isResizing() = 0;
		
		/**
		 * Notifies the current page that it has lost focus.
		 */
		virtual void unfocus() = 0;
		
		/**
		 * Notifies the current page that is has gained focus. You will need
		 * to call this to gain textbox focus, among other things. (If you
		 * fail to ever see a blinking caret when typing text, this is why).
		 */
		virtual void focus() = 0;
		
		/**
		 * Sets whether or not pages should be rendered with transparency
		 * preserved. (ex, for pages with style="background-color:transparent")
		 *
		 * @param	isTransparent	Whether or not this WebView is transparent.
		 */
		virtual void setTransparent(bool isTransparent) = 0;
		
		/**
		 * Sets the current URL Filtering Mode (default is UFM_NONE).
		 * See URLFilteringMode for more information on the modes.
		 *
		 * @param	mode	The URL filtering mode to use.
		 */
		virtual void setURLFilteringMode(URLFilteringMode mode) = 0;
		
		/**
		 * Adds a new URL Filter rule.
		 *
		 * @param	filter	A string with optional wildcards that describes a 
		 *                  certain URL.
		 *
		 * @note		For example, to match all URLs from the domain 
		 *              "google.com", your filter string might be:
		 *                  http://google.com/*
		 *
		 * @note		You may also use the "local://" scheme prefix to 
		 *              describe the URL to the base directory (set via 
		 *              WebCore::setBaseDirectory).
		 */
		virtual void addURLFilter(const std::wstring& filter) = 0;
		
		/**
		 * Clears all URL Filter rules.
		 */
		virtual void clearAllURLFilters() = 0;
		
		/**
		 * Defines a new Header Definition or updates it if it already exists.
		 *
		 * @param	name	The unique name of the Header Definition; this is 
		 *                  used to refer to it later in 
		 *                  WebView::addHeaderRewriteRule and 
		 *                  WebView::removeHeaderRewriteRulesByDefinitionName.
		 *
		 * @param	definition	The header definition, a map of key/values 
		 *                      representing an HTTP header.
		 */
		virtual void setHeaderDefinition(
								const std::string& name, 
								const Awesomium::HeaderDefinition& definition) = 0;
		
		/**
		 * Adds a new a header re-write rule. All requests whose URL matches the
		 * specified rule will have its  HTTP headers re-written with the 
		 * specified header definition before sending it to the server.
		 *
		 * @param	rule	A wide string with optional wildcards (*, ?) that 
		 *                  matches the URL(s) that will have its headers 
		 *                  re-written with the specified header definition.
		 *
		 * @param	name	The name of the header definition (specified in 
		 *                  WebView::setHeaderDefinition).
		 *
		 * @note		The case where a URL is matched by multiple rules is 
		 *              unsupported, only the first match will be used.
		 */
		virtual void addHeaderRewriteRule(const std::wstring& rule, 
										  const std::string& name) = 0;
		
		/**
		 * Removes a header re-write rule from this WebView.
		 *
		 * @param	rule	The rule to remove (should match the string 
		 *                  specified in WebView::addHeaderRewriteRule exactly).
		 */
		virtual void removeHeaderRewriteRule(const std::wstring& rule) = 0;
		
		/**
		 * Removes all header re-write rules that are using a certain header 
		 * definition.
		 *
		 * @param	name	The name of the header definition (specified in 
		 *                  WebView::setHeaderDefinition). If you specify an 
		 *                  empty string, this will remove ALL header re-write rules.
		 */
		virtual void removeHeaderRewriteRulesByDefinitionName(const std::string& name) = 0;
		
	protected:
		virtual ~WebView() {}
	};
	
}
		
#endif