#include <stdio.h>
#include <string.h>
#include <mpd/client.h>
#include <libnotify/notify.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

struct mpd_connection *conn = NULL;
struct mpd_song *song = NULL;
struct mpd_status *status = NULL;

const char *mpdroot = "~/media/music/";
const char *albumart = "cover.jpg";
const char *artist = NULL, *title = NULL, *path = NULL;

GError *gerror = NULL;
GdkPixbuf *icon = NULL;
NotifyNotification *notify = NULL;

int main() {
	char fullpath[100], text[100];
	char *buf = NULL, *sub = NULL, *state = NULL;
	
	conn = mpd_connection_new(NULL, 0, 10000);
	notify = notify_notification_new(NULL, NULL, NULL);
	notify_init("mpdnotify");

	while(mpd_run_idle_mask(conn, MPD_IDLE_PLAYER)) {
		mpd_command_list_begin(conn, true);
		mpd_send_status(conn);
		mpd_send_current_song(conn);
		mpd_command_list_end(conn);

		status = mpd_recv_status(conn);
		if(mpd_status_get_state(status) == MPD_STATE_PLAY)
			state = "Playing:";
		else if(mpd_status_get_state(status) == MPD_STATE_PAUSE)
			state = "Paused:";
		else
			state = "Stopped:";
		mpd_response_next(conn);
		song = mpd_recv_song(conn);

		if(song) {
			artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
			title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);
			path = mpd_song_get_uri(song);

			sprintf(text, "%s - %s", artist, title);

			buf = fullpath;
			sub = strrchr(path, '/');
			buf = strcpy(buf, mpdroot);
			buf = strncat(buf, path, strlen(path) - strlen(sub) + 1);
			buf = strcat(buf, albumart);
			icon = gdk_pixbuf_new_from_file(fullpath, NULL);

			if(icon)
				notify_notification_update(notify, state, text, NULL);
			else
				notify_notification_update(notify, state, text, "sound");
			notify_notification_set_icon_from_pixbuf(notify, icon);
			notify_notification_show(notify, &gerror);

			mpd_song_free(song);
		}
		mpd_response_finish(conn);
	}
	mpd_connection_free(conn);
	notify_uninit();
	return 0;
}
