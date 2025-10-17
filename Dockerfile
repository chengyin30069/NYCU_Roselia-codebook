FROM archlinux:latest AS maker

RUN echo 'ParallelDownloads = 5' >> /etc/pacman.conf

RUN pacman -Syu --noconfirm reflector rsync 
	

RUN rm /etc/pacman.d/mirrorlist && \
    reflector -f 10 -c Taiwan >> /etc/pacman.d/mirrorlist

RUN pacman -Syu --noconfirm texlive-basic texlive-latex texlive-latexrecommended texlive-latexextra \
    texlive-xetex texlive-pictures texlive-mathscience texlive-bibtexextra \
    texlive-fontsrecommended texlive-fontutils texlive-langcjk texlive-langchinese \
    biber make unzip 

WORKDIR /work

COPY *.otf .

COPY ttf/ ./ttf/

RUN cd ttf && \
    unzip 'DMCAsansserif9.0-20252.zip' && \
    unzip 'Noto_Sans.zip' && \
    ls | grep .ttf | xargs -I% -n1 install -Dm644 % /usr/share/fonts/ttf/% 

RUN mkdir -p /usr/share/fonts/otf && \
    cp ./NotoSerifTC-Medium.otf /usr/share/fonts/otf/NotoSerifTC-Medium.otf 

RUN fc-cache -fv

COPY . .

RUN make clean && \
    make all


FROM bash:5

WORKDIR /work

# Copy to a temporary location that won't be overridden by volume mount
COPY --from=maker /work/main.pdf /tmp/main.pdf

# Copy the file to the mounted volume and then show message
CMD ["sh", "-c", "cp /tmp/main.pdf /work/main.pdf && echo 'main.pdf is ready at /work/main.pdf'"]
