Name: 		pinedit
Version: 	0.0.3
Release: 	1rh73

Group:    Amusements/Games
Summary: 	Editor, 3D Modeller for Emilia Pinball.

Vendor:		Henrik Enqvist  (henqvist@users.sourceforge.net)
Packager: Henrik Enqvist  (henqvist@users.sourceforge.net)
License: 	GPL
URL: 	  	http://pinball.sourceforge.net
Source: 	http://prdownloads.sourceforge.net/pinball/%{name}-%{version}.tar.gz
#BuildRoot: 	%{_tmppath}/%{name}-%{version}-root
#Prefix: /usr
#Prefix: /etc

%description
Pinball editor.


%prep
%setup

%build
./configure --prefix=%{_prefix}
#make prefix=%{_prefix}
make


%install
#mkdir -p %{buildroot}%{_prefix}/bin
#make prefix=%{buildroot}%{_prefix} install
make install

#Install application link for X-Windows
install -d /etc/X11/applnk/Games
echo -e "[Desktop Entry]
Name=Emilia Pinball Editor
Comment=OpenGL pinball game
Exec=pinedit
Icon=pinball.xpm
Terminal=0
Type=Application" > /etc/X11/applnk/Games/EmiliaPinballEditor.desktop




%clean
#rm -rf %{buildroot}
make uninstall
rm /etc/X11/applnk/Games/EmiliaPinballEditor.desktop

%files
%defattr(-,root,root)
%doc AUTHORS COPYING INSTALL NEWS README
/etc/X11/applnk/Games/EmiliaPinballEditor.desktop
%{_bindir}/pinedit
%{_bindir}/pinball-template
%{_prefix}/share/pinedit/*



%changelog
* Wed Mar 05 2003 Henrik Enqvist
- removed buildroot to get it to work with libtool
* Fri Mar 08 2002 Michal Ambroz (O_O) <rebus@seznam.cz>
- initial pinball RPM
