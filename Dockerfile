FROM archlinux:latest

RUN pacman -Syu --noconfirm texlive-basic texlive-latex texlive-latexrecommended texlive-latexextra \
    texlive-xetex texlive-pictures texlive-mathscience texlive-bibtexextra \
    texlive-fontsrecommended texlive-fontutils \
    texlive-langcjk texlive-langchinese noto-fonts noto-fonts-cjk \
    biber make unzip

WORKDIR /work

COPY . .

RUN mkdir ttf-dmcasansserif && cd ttf-dmcasansserif && \
    curl -L -O 'https://typedesign.replit.app/DMCAsansserif9.0-20252.zip' && \
    unzip 'DMCAsansserif9.0-20252.zip' && \
    ls | grep .ttf | xargs -I% -n1 install -Dm644 % /usr/share/fonts/TTF/% && \
    cd - && rm -rf ttf-dmcasansserif

CMD ["make"]
